//////////////////////////////////////////////////////////////////////
// Tim Rudowski
// Christopher Bubeck
// Senior Project
// Due Date:  11/29/00
//
// Options.cpp : implementation file of the Game Options Dialog
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "bumpercars.h"
#include "car.h"
#include "Options.h"

// Gain access to our game variables and cars
extern gameVariables gV;
extern CAR * Cars;


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Options dialog
// NOTE:  The following few functions are Visual Studio 
// machine generated

Options::Options(CWnd* pParent /*=NULL*/)
	: CDialog(Options::IDD, pParent)
{
	//{{AFX_DATA_INIT(Options)
	m_Player1Name = _T("");
	m_Player2Name = _T("");
	m_LapBox = 0;
	m_TimeBox = 0;
	//}}AFX_DATA_INIT
}


void Options::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(Options)
	DDX_Text(pDX, IDC_PLAYERNAME1, m_Player1Name);
	DDX_Text(pDX, IDC_PLAYERNAME2, m_Player2Name);
	DDX_Text(pDX, IDC_LAPS, m_LapBox);
	DDV_MinMaxInt(pDX, m_LapBox, 1, 9);
	DDX_Text(pDX, IDC_TIME, m_TimeBox);
	DDV_MinMaxInt(pDX, m_TimeBox, 1, 5);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(Options, CDialog)
	//{{AFX_MSG_MAP(Options)
	ON_BN_CLICKED(IDC_RADIO1, OnRadio1)
	ON_BN_CLICKED(IDC_RADIO2, OnRadio2)
	ON_BN_CLICKED(IDC_RADIO4, OnRadio4)
	ON_BN_CLICKED(IDC_RADIO3, OnRadio3)
	ON_BN_CLICKED(IDC_RADIO0, OnRadio0)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

//////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////
//						Options::OnInitDialog()
//////////////////////////////////////////////////////////////////////
// This is called when the dialog first opens.

BOOL Options::OnInitDialog() 
{
	//set the edit box to default number of laps
	m_LapBox = gV.numberOfLaps;

	//set the other edit box to default time limit
	m_TimeBox = gV.timeLimit;

	//set the player's names to default
	m_Player1Name = gV.playerNames[0];
	m_Player2Name = gV.playerNames[1];

	// 'remember' the old values of play mode and # players 
	// in case the user presses CANCEL
	oldPlayMode = gV.playMode;
	oldNoPlayers = gV.localPlayers;

	// Initialize the dialog
	CDialog::OnInitDialog();
	
	return TRUE;  // return TRUE unless you set the focus to a control
}
//////////////////////////////////////////////////////////////////////




//////////////////////////////////////////////////////////////////////
// Options message handlers
//////////////////////////////////////////////////////////////////////

// When the radio buttons are clicked, the values for play mode
// and number of players change accordingly.

void Options::OnRadio0() 
{
	gV.playMode = 0;
}

void Options::OnRadio1() 
{
	gV.playMode = 1;
}

void Options::OnRadio2() 
{
	gV.playMode = 2;	
}

void Options::OnRadio3() 
{
	gV.localPlayers = 1;
}

void Options::OnRadio4() 
{
	gV.localPlayers = 2;
}


//////////////////////////////////////////////////////////////////////
//						Options::OnCancel()
//////////////////////////////////////////////////////////////////////
// This is called when the user presses CANCEL on the dialog.

void Options::OnCancel() 
{
	// reset our values to their old values
	gV.playMode = oldPlayMode;
	gV.localPlayers = oldNoPlayers;
	
	// Cancel the dialog
	CDialog::OnCancel();
}

//////////////////////////////////////////////////////////////////////



//////////////////////////////////////////////////////////////////////
//						Options::OnOK()
//////////////////////////////////////////////////////////////////////
// This is called when the user presses OK on the dialog.

void Options::OnOK() 
{
	double x, y;

	// Get the data from the dialog box
	UpdateData(TRUE);

	gV.numberOfLaps = m_LapBox;		//set number of laps to user input
	gV.timeLimit = m_TimeBox;		//set time limit to input

	// If the user entered a name, then save it in our player name
	// array
	if (!m_Player1Name.IsEmpty())
		gV.playerNames[0] = m_Player1Name;	

	if (!m_Player2Name.IsEmpty())
		gV.playerNames[1] = m_Player2Name;

	// Set the twoPlayers bool accordingly
	if (gV.localPlayers == 2)
		gV.twoPlayers = true;
	else
		gV.twoPlayers = false;

	// If the play mode is capture the flag, we use the capture the flag
	// board.
	if (gV.playMode == 2)
	{
		gV.trackChosen = 5;
		if (gV.mainTrack)
			delete gV.mainTrack;

		gV.mainTrack = new Track(5);

		gV.drawDynamite = false;
		gV.drawGear = false;
		gV.drawMedikit = false;
		gV.drawOil = false;

		gV.canCapture = true;
	}

	// Reset the number of laps and damage variables in the cars.
	// Also declare that nobody has won yet.
	// This means that when OK on the Options dialog is pressed, the
	// current game will be reset (a player cannot change options halfway
	// through a current game).
	Cars[gV.localCar[0]].reset();
	Cars[gV.localCar[1]].reset();
	gV.winner = -1;

	// Also, reset the cars back to their original starting positions
	// and directions
	gV.mainTrack->getStartingPosition(0, x, y);
	Cars[gV.localCar[0]].set_position(x, y);
	Cars[gV.localCar[0]].set_head_sector(gV.mainTrack->getStartingDirection());

	gV.mainTrack->getStartingPosition(1, x, y);
	Cars[gV.localCar[1]].set_position(x, y);
	Cars[gV.localCar[1]].set_head_sector(gV.mainTrack->getStartingDirection());
	
	// Close the dialog
	CDialog::OnOK();
}

//////////////////////////////////////////////////////////////////////
