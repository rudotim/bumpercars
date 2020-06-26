//////////////////////////////////////////////////////////////////////
// Tim Rudowski
// Christopher Bubeck
// Senior Project
// Due Date:  11/29/00
//
// bumpercarsDlg.cpp : implementation file of main Bumper Cars menu
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "bumpercars.h"
#include "bumpercarsDlg.h"
#include "multiplayer.h"
#include "choosetrack.h"
#include "choosecar.h"
#include "options.h"
#include "car.h"
#include "functions.h"
#include "mainplay.h"

#include <mmsystem.h>

// Create objects for our different dialogs
Multiplayer mpDlg;
choosetrack ctDlg;
Options oDlg;
choosecar ccDlg;

// Create the gameVariables struct declared in bumpercars.h
gameVariables gV;

// Gain access to our CAR data types
extern CAR * Cars;
extern BITMAP_IMAGE medikit;
extern BITMAP_IMAGE gear;
extern BITMAP_IMAGE oil;
extern BITMAP_IMAGE dynamite;

// This is how often (in sec) we add a new power up to the board
const int timeOutMedikit = 35;
const int timeOutGear = 30;
const int timeOutOil = 25;
const int timeOutDynamite = 20;


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

// NOTE:  Many of the functions here are Visual Studio generated.
// A ** indicates where our own initialization has been added.
// The Button handlers down the bottom, however, our entirely our own code.
//
/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About
//////////////////////////////////////////////////////////////////////

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CBumpercarsDlg dialog

CBumpercarsDlg::CBumpercarsDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CBumpercarsDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CBumpercarsDlg)
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CBumpercarsDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CBumpercarsDlg)
	DDX_Control(pDX, IDCANCEL, m_ExitCommand);
	DDX_Control(pDX, IDC_PLAY, m_PlayCommand);
	DDX_Control(pDX, IDC_CHOOSECAR, m_ChooseCar);
	DDX_Control(pDX, IDC_CHOOSETRACK, m_ChooseTrack);
	DDX_Control(pDX, IDC_MULTIPLAYER, m_Multiplayer);
	DDX_Control(pDX, IDC_OPTIONS, m_Options);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CBumpercarsDlg, CDialog)
	//{{AFX_MSG_MAP(CBumpercarsDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_CLOSE()
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_HELPBUTTON, OnHelpButton)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CBumpercarsDlg message handlers

BOOL CBumpercarsDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// ** //
	// Extra initialization here
	// First initialize the values of the private members of the class.
	// All the counters start out at 1.
	counterMedikit = 1;
	counterGear = 1;
	counterOil = 1;
	counterDynamite = 1;
	captureFlagCounter = 1;


	// Initialize the members of the gameVariables struct with default
	// values.

	gV.canCapture = true;				// Nobody has the flag initially 
	gV.drawGear = false;				// Initially none of the  
	gV.drawMedikit = false;				// power-ups are drawn
	gV.drawOil = false;					//
	gV.drawDynamite = false;
	gV.localPlayers = 1;				// One player
	gV.multiplayerEnabled = false;		// No multiplayer yet
	gV.playerNames[0] = "Player 1";		// Default player names
	gV.playerNames[1] = "Player 2";
	gV.localCar[0] = 0;					// Car[0] is blue (0) by default
	Cars[0].setCarNumber(0);			
	gV.localCar[1] = 1;					// Car[1] is red (1) by default
	Cars[1].setCarNumber(1);
	gV.numberOfLaps = 5;				// 5 laps
	gV.playMode = 0;					// Practice Mode by default
	gV.mainTrack = new Track(1);		// Street Course is default
	gV.trackChosen = 1;
	gV.timeLimit = 4;					// 4 minute time limit
	gV.twoPlayers = false;				// Only one player locally
	gV.winner = -1;						// No winner initially
	gV.whoHasFlag = -1;					// Noone has the flag initially

	double x, y;

	// Set the starting positions of the cars and their directions.
	// This is done here in case the user presses PLAY right away and
	// does not bother to set any options.

	gV.mainTrack->getStartingPosition(0, x, y);
	Cars[gV.localCar[0]].set_position(x, y);
	Cars[gV.localCar[0]].set_head_sector(gV.mainTrack->getStartingDirection());

	gV.mainTrack->getStartingPosition(1, x, y);
	Cars[gV.localCar[1]].set_position(x, y);
	Cars[gV.localCar[1]].set_head_sector(gV.mainTrack->getStartingDirection());
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CBumpercarsDlg::OnClose() 
{
	// ** //
	// Make sure we delete the main track when the application closes.
	// If not it will be leaked.
	
	if (gV.mainTrack)
		delete gV.mainTrack;
	
	CDialog::OnClose();
}

void CBumpercarsDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CBumpercarsDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CBumpercarsDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}


BEGIN_EVENTSINK_MAP(CBumpercarsDlg, CDialog)
    //{{AFX_EVENTSINK_MAP(CBumpercarsDlg)
	ON_EVENT(CBumpercarsDlg, IDCANCEL, -600 /* Click */, OnClickExit, VTS_NONE)
	ON_EVENT(CBumpercarsDlg, IDC_PLAY, -600 /* Click */, OnClickPlay, VTS_NONE)
	ON_EVENT(CBumpercarsDlg, IDC_MULTIPLAYER, -600 /* Click */, OnClickMultiplayer, VTS_NONE)
	ON_EVENT(CBumpercarsDlg, IDC_CHOOSETRACK, -600 /* Click */, OnClickChooseTrack, VTS_NONE)
	ON_EVENT(CBumpercarsDlg, IDC_CHOOSECAR, -600 /* Click */, OnClickChooseCar, VTS_NONE)
	ON_EVENT(CBumpercarsDlg, IDC_OPTIONS, -600 /* Click */, OnClickOptions, VTS_NONE)
	//}}AFX_EVENTSINK_MAP
END_EVENTSINK_MAP()


//////////////////////////////////////////////////////////////////////
//			Button message handlers (entirely our code)
//////////////////////////////////////////////////////////////////////


// When EXIT is clicked we end the dialog box and exit the program.
void CBumpercarsDlg::OnClickExit() 
{	
	EndDialog(IDCANCEL);	
}


// When PLAY is clicked, we know this is not a multiplayer game. So, we
// set the total players equal to how many players are on this machine, 
// and run the main game window.  Also, we set the timer for capture the
// flag/racing mode so we can keep track of a winner.  We kill this timer
// after the main window has closed (the game is paused).
void CBumpercarsDlg::OnClickPlay() 
{
	// No remote players
	gV.totalPlayers = gV.localPlayers;

	// Set our capture the flag/racing timer
	if (gV.playMode != 0)
		SetTimer(gV.playMode, 250, NULL);

	// Set power-up timer
	SetTimer(3, 1000, NULL);

	// Run the game
	runGame(0);

	// Kill timers and do other cleanup
	KillTimer(3);

	if (gV.playMode != 0)
		KillTimer(gV.playMode);

	gV.drawDynamite = false;
	gV.drawGear = false;
	gV.drawMedikit = false;
	gV.drawOil = false;
}


// Open the Multiplayer dialog when MULTIPLAYER is clicked.
void CBumpercarsDlg::OnClickMultiplayer() 
{
	mpDlg.DoModal();
	
}


// Open the Choose Track dialog when CHOOSE TRACK is clicked.
void CBumpercarsDlg::OnClickChooseTrack() 
{
	ctDlg.DoModal();	

}


// Open the Choose Car window when CHOOSE CAR is clicked.
void CBumpercarsDlg::OnClickChooseCar() 
{
	ccDlg.DoModal();

}


// Open the Options dialog when OPTIONS is clicked.
void CBumpercarsDlg::OnClickOptions() 
{
	oDlg.DoModal();

}


// Show Bumper Cars help screen
void CBumpercarsDlg::OnHelpButton() 
{
	ShellExecute(AfxGetMainWnd()->GetSafeHwnd(), "open", "bumpercars.chm",
		NULL, NULL, SW_SHOW);	
}



//////////////////////////////////////////////////////////////////////
//							Timer function
//////////////////////////////////////////////////////////////////////
// The timer here checks different aspects of the game.  
// When the timer is 3, we increment our power-up counter, and place
// a power-up on the board if need be.  If the
// timer has an identity of 1, then we are in racing mode.  Every clock
// cycle, the timer checks the status of how many laps each car has
// completed, and if a winner occurs, the winner variable is set.

void CBumpercarsDlg::OnTimer(UINT nIDEvent) 
{
	short i;
	int x, y;
	BSTR name;
	short type;
	int max = 0;

	switch (nIDEvent)
	{
		case 3:
			// We increment our counters every time a clock cycle is run
			counterMedikit++;
			counterGear++;
			counterOil++;
			counterDynamite++;

			// For each of the next few if statements, we check to see
			// if it is time to place another power-up on the board.
			// If this happens, we:
			// (1) Reset the counter
			// (2) Get a position from the track
			// (3) If we get a position, and the power-up is not already
			// drawn, we draw it and, if applicable, send the message
			// to other players
			// (4) Else, we release the position we just got from the track
			// This pattern is the same for each power-up we have.

			if (counterMedikit == timeOutMedikit)
			{
				counterMedikit = 1;
				gV.mainTrack->getRandomPosition(x, y);
				if (x && (y && (gV.drawMedikit == false)))
				{
					medikit.x = x;
					medikit.y = y;
					gV.drawMedikit = true;
					type = 1;

					if (gV.multiplayerEnabled)
						mpDlg.m_DirectPlay.Send_Draw_Message_To_All(&type, (short*)&x, (short*)&y);
				}
				else
					gV.mainTrack->releasePosition(x, y);
			}

			if (counterGear == timeOutGear)
			{
				counterGear = 1;
				gV.mainTrack->getRandomPosition(x, y);
				if (x && (y && (gV.drawGear == false)))
				{
					gear.x = x;
					gear.y = y;
					gV.drawGear = true;
					type = 2;

					if (gV.multiplayerEnabled)
						mpDlg.m_DirectPlay.Send_Draw_Message_To_All(&type, (short*)&x, (short*)&y);
				}
				else
					gV.mainTrack->releasePosition(x, y);
			}

			if (counterOil == timeOutOil)
			{
				counterOil = 1;
				gV.mainTrack->getRandomPosition(x, y);
				if (x && (y && (gV.drawOil == false)))
				{
					oil.x = x;
					oil.y = y;
					gV.drawOil = true;
					type = 3;

					if (gV.multiplayerEnabled)
						mpDlg.m_DirectPlay.Send_Draw_Message_To_All(&type, (short*)&x, (short*)&y);
				}
				else
					gV.mainTrack->releasePosition(x, y);
			}

			if (counterDynamite == timeOutDynamite)
			{
				counterDynamite = 1;
				gV.mainTrack->getRandomPosition(x, y);
				if (x && (y && (gV.drawDynamite == false)))
				{
					dynamite.x = x;
					dynamite.y = y;
					gV.drawDynamite = true;
					type = 4;

					if (gV.multiplayerEnabled)
						mpDlg.m_DirectPlay.Send_Draw_Message_To_All(&type, (short*)&x, (short*)&y);
				}
				else
					gV.mainTrack->releasePosition(x, y);
			}

			
			break;
		case 1:
			for (i = 0; i < gV.localPlayers; i++)
			{
				// Check each car's lap variable to the number of laps
				// they should have completed to win the game
				if (gV.numberOfLaps == Cars[gV.localCar[i]].getLapsCompleted())
					if (gV.winner == -1)
					{
						PlaySound("win.wav", NULL, SND_FILENAME | SND_ASYNC);

						gV.winner = gV.localCar[i];
						name = gV.playerNames[i].AllocSysString();

						short numToSend = short(gV.localCar[i]);

						// If multiplayer is enabled, send a message to the others
						// saying that a player on our machine has won the game.
						if (gV.multiplayerEnabled)
							mpDlg.m_DirectPlay.Send_Winner_Message_To_All(&numToSend, &name);
					}
			}
			break;
		case 2:
			// Increment our capture the flag counter
			captureFlagCounter++;

			// Depending on who has the flag, give them more time with it
			Cars[gV.whoHasFlag].increment_flag();

			if (captureFlagCounter == (gV.timeLimit * 240))
			{
				PlaySound("win.wav", NULL, SND_FILENAME | SND_ASYNC);

				for (i = 0; i < gV.localPlayers; i++)
				{
					short numToSend2;
					// See who has the flag longest.  Depending on who has
					// the flag longest, send a message to the other players
					if (Cars[gV.localCar[i]].get_flag_time() > max)
					{
						max = Cars[gV.localCar[i]].get_flag_time();

						gV.winner = gV.localCar[i];
						name = gV.playerNames[i].AllocSysString();
					}

					numToSend2 = short(gV.localCar[i]);

					if (gV.multiplayerEnabled)
						mpDlg.m_DirectPlay.Send_Winner_Message_To_All(&numToSend2, &name);
				}
			}
			break;
		default:
			break;
	}

	CDialog::OnTimer(nIDEvent);
}

//////////////////////////////////////////////////////////////////////

