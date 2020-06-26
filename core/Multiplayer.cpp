//////////////////////////////////////////////////////////////////////
// Tim Rudowski
// Christopher Bubeck
// Senior Project
// Due Date:  11/29/00
//
// Multiplayer.cpp : implementation file of the Multiplayer functions.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "bumpercars.h"
#include "bumpercarsDlg.h"
#include "Multiplayer.h"
#include "car.h"
#include "functions.h"
#include "mainplay.h"

#include <mmsystem.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

// Defines message types and ways to connect
// Also time-outs for receiving and sending messages

#define IPX		1
#define TCPIP	2
#define MODEM	3
#define SERIAL	4

#define PLAYCH	 0
#define CHAT	 1
#define POSITION 2
#define START	 3
#define BUMPED	 4
#define WINNER	 5
#define DRAW	 6
#define UNDRAW	 7
#define ACQUIRE	 8
#define UNACQ	 9

#define TIMEOUTSEND		40
#define TIMEOUTRECEIVE	30

// Gain access to our game variables, cars, and power-up images
extern gameVariables gV;
extern CAR * Cars;
extern BITMAP_IMAGE		gear;
extern BITMAP_IMAGE		medikit;
extern BITMAP_IMAGE		oil;
extern BITMAP_IMAGE		dynamite;

/////////////////////////////////////////////////////////////////////////////
// Multiplayer dialog
// NOTE:  The next 3 functions are Visual Studio generated.

Multiplayer::Multiplayer(CWnd* pParent /*=NULL*/)
	: CDialog(Multiplayer::IDD, pParent)
{
	//{{AFX_DATA_INIT(Multiplayer)
	m_Message = _T("");
	m_Connected = 0;
	m_MPlayerName1 = _T("");
	m_MPlayerName2 = _T("");
	m_MPlayerTrack = _T("");
	m_MPlayerNo = _T("");
	m_MPlayerMode = _T("");
	//}}AFX_DATA_INIT

}


void Multiplayer::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(Multiplayer)
	DDX_Control(pDX, IDC_MESSAGE, m_EditMessage);
	DDX_Control(pDX, IDC_STARTGAME, m_StartGame);
	DDX_Control(pDX, IDC_SEND, m_Send);
	DDX_Control(pDX, IDC_JOIN, m_Join);
	DDX_Control(pDX, IDC_CREATE, m_Create);
	DDX_Control(pDX, IDC_CHATBOX, m_ChatBox);
	DDX_Control(pDX, IDC_DPLAYCONTROL1, m_DirectPlay);
	DDX_Text(pDX, IDC_MESSAGE, m_Message);
	DDX_Text(pDX, IDC_CONNECTED, m_Connected);
	DDV_MinMaxInt(pDX, m_Connected, 0, 6);
	DDX_Text(pDX, IDC_MPLAYERNAME1, m_MPlayerName1);
	DDX_Text(pDX, IDC_MPLAYERNAME2, m_MPlayerName2);
	DDX_Text(pDX, IDC_MPLAYERTRACK, m_MPlayerTrack);
	DDX_Text(pDX, IDC_MPLAYERNO, m_MPlayerNo);
	DDX_Text(pDX, IDC_MPLAYERMODE, m_MPlayerMode);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(Multiplayer, CDialog)
	//{{AFX_MSG_MAP(Multiplayer)
	ON_BN_CLICKED(IDC_CREATE, OnCreate)
	ON_BN_CLICKED(IDC_JOIN, OnJoin)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_STARTGAME, OnStartGame)
	ON_BN_CLICKED(IDC_SEND, OnSend)
	ON_BN_CLICKED(IDC_IPX, OnIPX)
	ON_BN_CLICKED(IDC_TCPIP, OnTCPIP)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()
//////////////////////////////////////////////////////////////////////



//////////////////////////////////////////////////////////////////////
//					Multiplayer::OnInitDialog()
//////////////////////////////////////////////////////////////////////
// This is called when the dialog box first opens.

BOOL Multiplayer::OnInitDialog() 
{
	char result[1];
	
	// We want to show the player names, the number of local players,
	// the track selected, and game mode in this screen.  This is
	// accomplished with the next few lines of code.

	m_MPlayerName1 = gV.playerNames[0];
	if (gV.twoPlayers)
		m_MPlayerName2 = gV.playerNames[1];

	m_MPlayerNo = itoa(gV.localPlayers, result, 10);

	switch (gV.trackChosen)
	{
		case 1:
			m_MPlayerTrack = "Street Course";
			break;
		case 2:
			m_MPlayerTrack = "Junkyard Course";
			break;
		case 3:
			m_MPlayerTrack = "Heavy Metal Course";
			break;
		case 4:
			m_MPlayerTrack = "Thanksgiving Course";
			break;
		case 5:
			m_MPlayerTrack = "Beach Course";
			break;
		default:
			break;
	}

	switch (gV.playMode)
	{
		case 0:
			m_MPlayerMode = "Practice Mode";
			break;
		case 1:
			m_MPlayerMode = "Racing Mode";
			break;
		case 2:
			m_MPlayerMode = "Capture The Flag";
			break;
		default:
			break;
	}

	// We have not started yet
	alreadyStarted = false;

	// This is used when sending messages
	// Here it is initialized.
	oldMessage = _T("");

	// Default way to connect is TCPIP
	Connection = TCPIP;

	CDialog::OnInitDialog();
	
	return TRUE;  // return TRUE unless you set the focus to a control
}
//////////////////////////////////////////////////////////////////////



//////////////////////////////////////////////////////////////////////
//					Multiplayer::OnCancel()
//////////////////////////////////////////////////////////////////////
// This is called when the user presses the EXIT button.

void Multiplayer::OnCancel() 
{
	// Kill timers, and disable the multiplayer variable.
	KillTimer(2);
	AfxGetMainWnd()->KillTimer(3);
	gV.multiplayerEnabled = false;
	
	CDialog::OnCancel();
}

//////////////////////////////////////////////////////////////////////



//////////////////////////////////////////////////////////////////////
//					Multiplayer::OnCreate()
//////////////////////////////////////////////////////////////////////
// This is called when the user presses the CREATE SESSION button.

void Multiplayer::OnCreate() 
{
	BOOL temp;
	short MaxPlay;
	BSTR SessName;
	BSTR PlayName1;
	BSTR PlayName2;

	// Get data from the dialog
	UpdateData(TRUE);

	// As of now, Bumper Cars only supports 4 players at once, although
	// theoretically it could support more once more cars are designed.
	MaxPlay = 4;

	// Fill in session name, and player names
	SessName = L"Bumper Cars";
	PlayName1 = gV.playerNames[0].AllocSysString();
	PlayName2 = gV.playerNames[1].AllocSysString();

	// Here is where we start using the VB control
	// First, we have to initialize the connection with the IPX or
	// TCP/IP protocol.
	temp = m_DirectPlay.Initialize_Connection(&Connection);

	// Now, we create a session
	temp = m_DirectPlay.Create_Session(&MaxPlay, &SessName);

	// We also create players, and save their IDs
	gV.playerIDs[0] = m_DirectPlay.Create_Player(&PlayName1);

	if (gV.twoPlayers)
		gV.playerIDs[1] = m_DirectPlay.Create_Player(&PlayName2);
	
	// Multiplayer is now enabled
	gV.multiplayerEnabled = true;
	

	// We hide our create/join buttons, and show the chat window
	m_Create.ShowWindow(SW_HIDE);
	m_Join.ShowWindow(SW_HIDE);
	m_Send.ShowWindow(SW_SHOW);
	m_StartGame.ShowWindow(SW_SHOW);
	m_ChatBox.ShowWindow(SW_SHOW);
	m_EditMessage.ShowWindow(SW_SHOW);

	// We update the players connected box
	m_Connected = m_DirectPlay.Get_Num_Players_Connected();
	UpdateData(FALSE);

	// Now, we set the timer to receive messages every so often.
	// This is used for primarily for chat messages and when new
	// players connect.

	SetTimer(2, TIMEOUTRECEIVE, NULL);
}

//////////////////////////////////////////////////////////////////////



//////////////////////////////////////////////////////////////////////
//					Multiplayer::OnJoin()
//////////////////////////////////////////////////////////////////////
// This is called when the user presses the JOIN SESSION button.
// This function is very similar to the one above.  One major difference
// is that a session is joined, not created, using the DPlay control.
// Also, we do not enable the 'Start Game' button.

void Multiplayer::OnJoin() 
{
	BOOL temp;
	BSTR PlayName1;
	BSTR PlayName2;

	UpdateData(TRUE);

	PlayName1 = gV.playerNames[0].AllocSysString();
	PlayName2 = gV.playerNames[1].AllocSysString();

	temp = m_DirectPlay.Initialize_Connection(&Connection);

	// Join, rather than Create, a session
	temp = m_DirectPlay.Join_Session();

	gV.playerIDs[0] = m_DirectPlay.Create_Player(&PlayName1);

	if (gV.twoPlayers)
		gV.playerIDs[1] = m_DirectPlay.Create_Player(&PlayName2);
	
	gV.multiplayerEnabled = true;

	m_Create.ShowWindow(SW_HIDE);
	m_Join.ShowWindow(SW_HIDE);
	m_Send.ShowWindow(SW_SHOW);
	m_ChatBox.ShowWindow(SW_SHOW);
	m_EditMessage.ShowWindow(SW_SHOW);

	m_Connected = m_DirectPlay.Get_Num_Players_Connected();
	UpdateData(FALSE);

	SetTimer(2, TIMEOUTRECEIVE, NULL);
}

//////////////////////////////////////////////////////////////////////



//////////////////////////////////////////////////////////////////////
//				Multiplayer::OnPositionMessageReceived()
//////////////////////////////////////////////////////////////////////
// This is called when we receive a position message.

void Multiplayer::OnPositionMessageReceived() 
{
	short car;
	short direction;
	double x, y;
	double accel;

	// We get the car's number, direction, position, and speed.
	// We then update the data, so when Game_Main() draws the cars,
	// they will be in the correct position.

	m_DirectPlay.Get_Position_Message(&car, &direction, &x, &y, &accel);

	Cars[car].set_position(x, y);
	Cars[car].set_head_sector(direction);
	Cars[car].set_speed(accel);

}
//////////////////////////////////////////////////////////////////////



//////////////////////////////////////////////////////////////////////
//					Multiplayer::OnTimer(UINT)
//////////////////////////////////////////////////////////////////////
// Whenever a time-out occurs, this function is called.
// There are two cases in which we set a time-out:
// (1) for periodically sending position messages, and
// (2) for periodically receiving messages
// This function handles both cases.

void Multiplayer::OnTimer(UINT nIDEvent) 
{
	short car;
	short direction;
	double x, y, accel;
	int i;

	switch (nIDEvent)
	{
		case 1:

			// In this case, we are sending a position message.
			// We get the car's vital data, such as its position, speed,
			// and direction, and pass it to the DirectPlay control.
			// We send the message to everyone so that all players can
			// update their screens.

			for (i = 0; i < gV.localPlayers; i++)
			{
				car = short(gV.localCar[i]);

				Cars[car].get_position(x, y);
				direction = Cars[car].get_head_sector();
				accel = Cars[car].get_speed();
				m_DirectPlay.Send_Position_Message_To_All(&car, &direction, &x, &y, &accel);
			}
			break;
		case 2:

			// In this case, we want to receive messages by calling
			// the receive function
			Receive();
			break;
		default:
			break;
	}

	CDialog::OnTimer(nIDEvent);
}
//////////////////////////////////////////////////////////////////////




//////////////////////////////////////////////////////////////////////
//					Multiplayer::Receive()
//////////////////////////////////////////////////////////////////////
// This is called when we want to receive messages.
// 

void Multiplayer::Receive()
{
	long Count;
	int whichMessage;

	// First, we see how many messages are waiting in the message
	// queue. If there are any messages, we execute the while 
	// statement below.
	Count = m_DirectPlay.Get_Message_Count();

	while (Count > 0)
	{
		// Find out which message it is
		whichMessage = m_DirectPlay.GetDPMessage();

		// Depending on which message we want to process, invoke the
		// appropriate function
		switch (whichMessage)
		{
			case PLAYCH:
				OnNumberPlayersChanged();
				break;
			case CHAT:
				OnChatMessageReceived();
				break;
			case POSITION:
				OnPositionMessageReceived();
				break;
			case START:
				OnStartMessageReceived();
				break;
			case BUMPED:
				OnBumpMessageReceived();
				break;
			case WINNER:
				OnWinnerMessageReceived();
				break;
			case DRAW:
				OnDrawMessageReceived();
				break;
			case UNDRAW:
				OnUnDrawMessageReceived();
				break;
			case ACQUIRE:
				OnAcquireMessageReceived();
				break;
			case UNACQ:
				OnUnAcquireMessageReceived();
				break;
			default:
				break;
		}
		Count--;
	}
}
//////////////////////////////////////////////////////////////////////



//////////////////////////////////////////////////////////////////////
//					Multiplayer::OnStartGame()
//////////////////////////////////////////////////////////////////////
// This is called when the user who has created a multiplayer session
// presses the "START GAME" button.
//
// It is also called when the button changes to "RESUME GAME" and it
// is pressed.

void Multiplayer::OnStartGame() 
{
	short i;
	short totPlay, trChosen, mode, data;
	double x, y;

	// If we have already started the game, then we do NOT want to do
	// any initialization.  This occurs when "RESUME GAME" is pressed.

	if (!alreadyStarted)
	{
		// DirectPlay stores a list of all players connected in a game,
		// and basically assigns each player a number.  This is useful
		// to use in the game, and we use it to set player's car colors.
		// The for loop checks our playerID #s to the values DirectPlay
		// has.  If the values match, we assign that unique number to
		// the car.  
		// This also means that players cannot choose their own car color
		// in Multiplayer mode.  This was designed to make the
		// development easier, to avoid players "fighting" over car colors
		// and such.

		for (i = 1; i <= m_DirectPlay.Get_Num_Players_Connected(); i++)
		{
			if (gV.playerIDs[0] == m_DirectPlay.Get_PlayerID(&i))
			{
				gV.localCar[0] = (i - 1);
				Cars[(i - 1)].setCarNumber(0);
			}
			else 
				if (gV.playerIDs[1] == m_DirectPlay.Get_PlayerID(&i))
				{
					gV.localCar[1] = (i - 1);
					Cars[(i - 1)].setCarNumber(1);
				}
		}

		// We get a count of all players connected
		gV.totalPlayers = m_DirectPlay.Get_Num_Players_Connected();

		// Typecast some ints to shorts
		totPlay = short(gV.totalPlayers);
		trChosen = short(gV.trackChosen);
		mode = short(gV.playMode);

		// Depending on what mode we are in, we want to send info such
		// as number of laps needed to win the game, or the time limit.
		switch (gV.playMode)
		{
			case 0:
				data = 0;
				break;
			case 1:
				data = gV.numberOfLaps;
				break;
			case 2:
				data = gV.timeLimit;
				break;
			default:
				break;
		}

		// Set the starting position and direction of each car
		gV.mainTrack->getStartingPosition(gV.localCar[0], x, y);
		Cars[gV.localCar[0]].set_position(x, y);
		Cars[gV.localCar[0]].set_head_sector(gV.mainTrack->getStartingDirection());

		if (gV.twoPlayers)
		{
			gV.mainTrack->getStartingPosition(gV.localCar[1], x, y);
			Cars[gV.localCar[1]].set_position(x, y);
			Cars[gV.localCar[1]].set_head_sector(gV.mainTrack->getStartingDirection());

			// If there are two players locally, we want to destroy
			// one of them.  This avoids duplicate messages being 
			// received.
			m_DirectPlay.Destroy_Player(&gV.playerIDs[1]);
		}

		// Tell other machines to start a game
		// Give them info such as total players, the track, game mode,
		// and number of laps/time limit
		m_DirectPlay.Send_Start_Message_To_All(&totPlay, &trChosen, &mode, &data);

		// This sets the power-up timer in bumpercarsDlg.cpp
		AfxGetMainWnd()->SetTimer(3, 1000, NULL);

		// If we are in capture the flag mode, this sets that timer
		// (also in bumpercarsDlg.cpp)
		if (gV.playMode == 2)
			AfxGetMainWnd()->SetTimer(2, 250, NULL);
	}

	// Minimize the dialog
	ShowWindow(SW_MINIMIZE);
	
	// Start sending position messages every TIMEOUTSEND msec, and 
	// stop periodically receiving messages.
	// During the game, we will receive messages in the Game_Main()
	// function.
	SetTimer(1, TIMEOUTSEND, NULL);
	KillTimer(2);

	// If we are in racing mode, we want to set the timer to start
	// counting laps (bumpercarsDlg.cpp)
	if (gV.playMode == 1)
		AfxGetMainWnd()->SetTimer(1, 250, NULL);

	// Actually open the main DirectDraw window and start playing
	runGame(0);

	// Kill lap timer after user has exited the main window
	if (gV.playMode == 1)
		AfxGetMainWnd()->KillTimer(1);

	// Stop sending position messages and periodically receive
	// messages.
	KillTimer(1);
	SetTimer(2, TIMEOUTRECEIVE, NULL);
	
	// Restore the dialog
	ShowWindow(SW_RESTORE);

	// Show our "RESUME GAME" dialog, and say we have already started
	m_StartGame.ShowWindow(SW_SHOW);
	m_StartGame.SetWindowText("Resume Game");
	alreadyStarted = true;
}
//////////////////////////////////////////////////////////////////////



//////////////////////////////////////////////////////////////////////
//				Multiplayer::OnNumberPlayersChanged()
//////////////////////////////////////////////////////////////////////
// When the number of players changes, we update the box in the
// lower left corner of the screen.

void Multiplayer::OnNumberPlayersChanged() 
{
	m_Connected = m_DirectPlay.Get_Num_Players_Connected();
	UpdateData(FALSE);
}
//////////////////////////////////////////////////////////////////////




//////////////////////////////////////////////////////////////////////
//				Multiplayer::OnStartMessageReceived()
//////////////////////////////////////////////////////////////////////
// This is called when another machine has sent us a start message.
// 
// This is very similar to the OnStartGame() function above, although
// subtle differences will not allow the two to be the same function.

void Multiplayer::OnStartMessageReceived() 
{
	short i;
	short totPlay, trChosen, mode, data;
	double x, y;

	// The idea here is similar to the above:
	// Assign numbers (car colors) to individual players

	if (!alreadyStarted)
	{
		for (i = 1; i <= m_DirectPlay.Get_Num_Players_Connected(); i++)
		{
			if (gV.playerIDs[0] == m_DirectPlay.Get_PlayerID(&i))
			{
				gV.localCar[0] = (i - 1);
				Cars[(i - 1)].setCarNumber(0);
			}
			else 
				if (gV.playerIDs[1] == m_DirectPlay.Get_PlayerID(&i))
				{
					gV.localCar[1] = (i - 1);
					Cars[(i - 1)].setCarNumber(1);
				}
		}

		// Retrieve the data sent to us and store it in the 
		// game variables
		m_DirectPlay.Get_Start_Message(&totPlay, &trChosen, &mode, &data);

		gV.totalPlayers = totPlay;
		gV.trackChosen = trChosen;
		gV.playMode = mode;
	
		// If there is a previous track, delete it
		if (gV.mainTrack)
			delete gV.mainTrack;

		// Then set the new track with the one the user has chosen
		gV.mainTrack = new Track(gV.trackChosen);

		// Set the starting position and direction of each car
		gV.mainTrack->getStartingPosition(0, x, y);
		Cars[gV.localCar[0]].set_position(x, y);
		Cars[gV.localCar[0]].set_head_sector(gV.mainTrack->getStartingDirection());

		if (gV.twoPlayers)
		{
			gV.mainTrack->getStartingPosition(1, x, y);
			Cars[gV.localCar[1]].set_position(x, y);
			Cars[gV.localCar[1]].set_head_sector(gV.mainTrack->getStartingDirection());

			// Also, destroy the extra player here, so we do not
			// receive extra messages.
			m_DirectPlay.Destroy_Player(&gV.playerIDs[1]);
		}

		// Remember the switch in the above function that sent number 
		// of laps/time limit?  Here we retrieve it.
		// (The switches are subtly different)
		switch (gV.playMode)
		{
			case 0:
				break;
			case 1:
				gV.numberOfLaps = data; 
				break;
			case 2:
				gV.timeLimit = data;
				break;
			default:
				break;
		}

		// Record we have done our initialization
		alreadyStarted = true;

		// Actually call OnStartGame() to minimize dialog, etc.
		// It will not do any initialization since alreadyStarted
		// is true.
		OnStartGame();
	}
}
//////////////////////////////////////////////////////////////////////




//////////////////////////////////////////////////////////////////////
//				Multiplayer::OnChatMessageReceived()
//////////////////////////////////////////////////////////////////////
// This is called when we receive a chat message.

void Multiplayer::OnChatMessageReceived() 
{
	CString Message;

	// See what the message is
	Message = m_DirectPlay.Get_Chat_Message();

	// Because there could be 2 players on a machine, a message
	// could be sent to the other player on our machine, which results
	// in duplicate messages in the chat window.
	// To avoid this, we set oldMessage to the message we have sent.
	// If they are the same, we do not add it to the box.
	// This avoids duplicate messages.

	if (oldMessage != Message)
		m_ChatBox.AddString(Message);

	oldMessage = Message;
	
}
//////////////////////////////////////////////////////////////////////



//////////////////////////////////////////////////////////////////////
//						Multiplayer::OnSend()
//////////////////////////////////////////////////////////////////////
// This is used to send chat messages, and is called when the 
// "SEND MESSAGE" button is pressed.

void Multiplayer::OnSend() 
{
	UpdateData(TRUE);

	// Get the chat message from the box, and add the player's name
	BSTR Param;
	CString Total = gV.playerNames[0] + "> " + m_Message;
	Param = Total.AllocSysString();

	// Add the message to our chat box, and send the message
	// to everyone.
	m_ChatBox.AddString(Total);
	m_DirectPlay.Send_Chat_Message_To_All(&Param);

	// Erase the message from the box, and save it in oldMessage
	m_Message = _T("");
	m_EditMessage.SetFocus();
	oldMessage = Total;
	UpdateData(FALSE);
	
}
//////////////////////////////////////////////////////////////////////




//////////////////////////////////////////////////////////////////////
//				Multiplayer::OnBumpMessageReceived()
//////////////////////////////////////////////////////////////////////
// This is called when someone has been bumped.

void Multiplayer::OnBumpMessageReceived()
{
	short car;
	short damage;
	BOOL goForwards;

	PlaySound("crash.wav", NULL, SND_FILENAME | SND_ASYNC);

	// Get the car number, the damage it has taken, and which direction
	// it should go in.
	m_DirectPlay.Get_Bumped_Message(&car, &damage, &goForwards);

	// If it is one of our cars, then increment its damage, and
	// send it where it should go.

	if ((car == gV.localCar[0]) || (car == gV.localCar[1]))
	{
		Cars[car].raise_damage( damage );

		if (goForwards)
			Cars[car].set_speed(2.5);
		else
			Cars[car].set_speed(-3.0);


		Cars[car].move();
	}
}
//////////////////////////////////////////////////////////////////////




//////////////////////////////////////////////////////////////////////
//				Multiplayer::OnWinnerMessageReceived()
//////////////////////////////////////////////////////////////////////
// This is called when we receive a message that someone has won the
// game.

void Multiplayer::OnWinnerMessageReceived()
{
	short winner;
	BSTR winnerName;
	CString temp;

	// Allocate the BSTR to avoid problems
	temp = "Temp";
	winnerName = temp.AllocSysString();

	PlaySound("win.wav", NULL, SND_FILENAME | SND_ASYNC);

	// Get the winner's car number and name
	m_DirectPlay.Get_Winner_Message(&winner, &winnerName);

	// Store these variables.  When Game_Main() loops around,
	// the player's name will be shown on screen.
	gV.winner = winner;
	gV.playerNames[winner] = winnerName;

}
//////////////////////////////////////////////////////////////////////




//////////////////////////////////////////////////////////////////////
//				Multiplayer::OnDrawMessageReceived()
//////////////////////////////////////////////////////////////////////
// This is called when a power-up has been added to the board, and
// we want to start drawing it.

void Multiplayer::OnDrawMessageReceived()
{
	short powerUpType;
	short x, y;

	// "Ask" what type it is and where it should go
	m_DirectPlay.Get_PowerUp_Message(&powerUpType, &x, &y);

	// Depending on the type of power-up, start drawing it in its
	// position.
	switch (powerUpType)
	{
		case 1:
			gV.drawMedikit = true;
			medikit.x = x;
			medikit.y = y;
			break;
		case 2:
			gV.drawGear = true;
			gear.x = x;
			gear.y = y;
			break;
		case 3:
			gV.drawOil = true;
			oil.x = x;
			oil.y = y;
			break;
		case 4:
			gV.drawDynamite = true;
			dynamite.x = x;
			dynamite.y = y;
			break;
		default:
			break;
	}
}
//////////////////////////////////////////////////////////////////////



//////////////////////////////////////////////////////////////////////
//				Multiplayer::OnUnDrawMessageReceived()
//////////////////////////////////////////////////////////////////////
// This is called when a car has run over a power-up, and we wish to 
// stop drawing it.

void Multiplayer::OnUnDrawMessageReceived()
{
	short powerUpType;
	short x, y;

	// We "Ask" what type of power-up it is, and its position
	m_DirectPlay.Get_PowerUp_Message(&powerUpType, &x, &y);

	// Depending on what type it is, we stop drawing it and play the
	// appropriate sound.
	switch (powerUpType)
	{
		case 1:
			gV.drawMedikit = false;
			PlaySound("powerup.wav", NULL, SND_FILENAME | SND_ASYNC);
			break;
		case 2:
			gV.drawGear = false;
			PlaySound("powerup.wav", NULL, SND_FILENAME | SND_ASYNC);
			break;
		case 3:
			gV.drawOil = false;
			PlaySound("powerdown.wav", NULL, SND_FILENAME | SND_ASYNC);
			break;
		case 4:
			gV.drawDynamite = false;
			PlaySound("dynamite.wav", NULL, SND_FILENAME | SND_ASYNC);
			break;
		default:
			break;
	}
}
//////////////////////////////////////////////////////////////////////



//////////////////////////////////////////////////////////////////////
//			Multiplayer::OnAcquireMessageReceived()
//////////////////////////////////////////////////////////////////////
// This is received when a player gains the flag.

void Multiplayer::OnAcquireMessageReceived()
{
	short carWithFlag;

	PlaySound("powerup.wav", NULL, SND_FILENAME | SND_ASYNC);

	// "Ask" the control which car has the flag now
	m_DirectPlay.Get_Acquire_Message(&carWithFlag);

	// Give that car the flag, and disable other cars from 
	// capturing it.
	Cars[carWithFlag].acquire_flag();
	gV.whoHasFlag = carWithFlag;
	gV.canCapture = false;
}
//////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////
//			Multiplayer::OnUnAcquireMessageReceived()
//////////////////////////////////////////////////////////////////////
// This is received when a player explodes and loses the flag.

void Multiplayer::OnUnAcquireMessageReceived()
{
	// The car who had the flag loses it
	Cars[gV.whoHasFlag].lose_flag();

	// Nobody has the flag, and it can be captured
	gV.whoHasFlag = -1;
	gV.canCapture = true;
}
//////////////////////////////////////////////////////////////////////



// When the appropriate radio button is pressed, change the type of
// connection we are using...

void Multiplayer::OnIPX() 
{
	Connection = IPX;	
}

void Multiplayer::OnTCPIP() 
{
	Connection = TCPIP;	
}


