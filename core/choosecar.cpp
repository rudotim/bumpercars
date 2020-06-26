//////////////////////////////////////////////////////////////////////
// Tim Rudowski
// Christopher Bubeck
// Senior Project
// Due Date:  11/29/00
//
// choosecar.cpp : implementation file
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "bumpercars.h"
#include "choosecar.h"
#include "mainplay.h"
#include "car.h"

extern gameVariables gV;
extern CAR * Cars;

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// NOTE:  The next 3 functions are Visual Studio generated.

choosecar::choosecar(CWnd* pParent /*=NULL*/)
	: CDialog(choosecar::IDD, pParent)
{
	//{{AFX_DATA_INIT(choosecar)
	m_Player1Car = _T("");
	m_Player2Car = _T("");
	//}}AFX_DATA_INIT
}


void choosecar::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(choosecar)
	DDX_Text(pDX, IDC_PLAYER1CAR, m_Player1Car);
	DDX_Text(pDX, IDC_PLAYER2CAR, m_Player2Car);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(choosecar, CDialog)
	//{{AFX_MSG_MAP(choosecar)
	ON_BN_CLICKED(IDC_CCPLAYER1, OnPlayer1)
	ON_BN_CLICKED(IDC_CCPLAYER2, OnPlayer2)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

//////////////////////////////////////////////////////////////////////



//////////////////////////////////////////////////////////////////////
//					choosecar::OnInitDialog()
//////////////////////////////////////////////////////////////////////
// This is called when the dialog first opens.

BOOL choosecar::OnInitDialog() 
{	
	// For the two cars, depending on the current color of the car,
	// display it to the user.
	switch (gV.localCar[0])
	{
		case 0:
			m_Player1Car = "Blue";
			break;
		case 1:
			m_Player1Car = "Red";
			break;
		case 2:
			m_Player1Car = "Green";
			break;
		case 3:
			m_Player1Car = "Yellow";
			break;
	}

	switch (gV.localCar[1])
	{
		case 0:
			m_Player2Car = "Blue";
			break;
		case 1:
			m_Player2Car = "Red";
			break;
		case 2:
			m_Player2Car = "Green";
			break;
		case 3:
			m_Player2Car = "Yellow";
			break;
	}

	CDialog::OnInitDialog();
	
	return TRUE;  // return TRUE unless you set the focus to a control

}
//////////////////////////////////////////////////////////////////////



//////////////////////////////////////////////////////////////////////
//					choosecar::OnPlayer1()
//////////////////////////////////////////////////////////////////////
// This is called when the user presses the "CHANGE CAR" button inside
// of the Player 1 frame.

void choosecar::OnPlayer1() 
{
	double x, y;

	// "Remember" the old value of the car
	int oldCarNo = gV.localCar[0];

	// Call the function to open the DirectDraw window.  It will return
	// a value which equals the number of the car the user has picked.
	// We now set the player's car to this number.
	gV.localCar[0] = runGame(1);

	// Two players cannot have the same car color.  If they do, then 
	// change our car color back to what we had before.
	if (gV.localCar[0] == gV.localCar[1])
		gV.localCar[0] = oldCarNo;

	// Refresh the display for the user.
	// Also, if the user pressed ESC over a car that is not currently
	// implemented, change the color back to its previous value.
	switch (gV.localCar[0])
	{
		case 0:
			m_Player1Car = "Blue";
			break;
		case 1:
			m_Player1Car = "Red";
			break;
		case 2:
			m_Player1Car = "Green";
			break;
		case 3:
			m_Player1Car = "Yellow";
			break;
		default:
			gV.localCar[0] = oldCarNo;
			break;
	}
	
	// Set the car number so that it knows where to start
	Cars[gV.localCar[0]].setCarNumber(0);

	// Set the starting position and direction of the car
	gV.mainTrack->getStartingPosition(0, x, y);
	Cars[gV.localCar[0]].set_position(x, y);
	Cars[gV.localCar[0]].set_head_sector(gV.mainTrack->getStartingDirection());

	UpdateData(FALSE);
}
//////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////
//					choosecar::OnPlayer2()
//////////////////////////////////////////////////////////////////////
// This is called when Player 2 wants to select a car color.
// This is similar to the function above, but has to be duplicated
// since we use the m_Player2Car variable instead of the m_Player1Car
// variable.

void choosecar::OnPlayer2() 
{
	double x, y;
	int oldCarNo = gV.localCar[1];

	gV.localCar[1] = runGame(1);

	if (gV.localCar[0] == gV.localCar[1])
		gV.localCar[1] = oldCarNo;

	switch (gV.localCar[1])
	{
		case 0:
			m_Player2Car = "Blue";
			break;
		case 1:
			m_Player2Car = "Red";
			break;
		case 2:
			m_Player2Car = "Green";
			break;
		case 3:
			m_Player2Car = "Yellow";
			break;
		default:
			gV.localCar[1] = oldCarNo;
			break;
	}

	Cars[gV.localCar[1]].setCarNumber(1);

	gV.mainTrack->getStartingPosition(1, x, y);
	Cars[gV.localCar[1]].set_position(x, y);
	Cars[gV.localCar[1]].set_head_sector(gV.mainTrack->getStartingDirection());

	UpdateData(FALSE);
	
}
//////////////////////////////////////////////////////////////////////

