//////////////////////////////////////////////////////////////////////
// Tim Rudowski
// Christopher Bubeck
// Senior Project
// Due Date:  11/29/00
//
// choosetrack.cpp : implementation file of the Choose Track dialog
//
// This dialog also derives from the MFC object CDialog.
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "bumpercars.h"
#include "choosetrack.h"
#include "car.h"
#include "functions.h"

// Gain access to the cars and to the game Variables
extern gameVariables gV;
extern CAR * Cars;
extern BITMAP_IMAGE medikit;
extern BITMAP_IMAGE gear;
extern BITMAP_IMAGE oil;
extern BITMAP_IMAGE dynamite;


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//////////////////////////////////////////////////////////////////////
// choosetrack dialog
//////////////////////////////////////////////////////////////////////
// NOTE:  The next 3 functions are Visual Studio generated.


choosetrack::choosetrack(CWnd* pParent /*=NULL*/)
	: CDialog(choosetrack::IDD, pParent)
{
	//{{AFX_DATA_INIT(choosetrack)
	//}}AFX_DATA_INIT
}


void choosetrack::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(choosetrack)
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(choosetrack, CDialog)
	//{{AFX_MSG_MAP(choosetrack)
	ON_BN_CLICKED(IDC_RADIO1, OnRadio1)
	ON_BN_CLICKED(IDC_RADIO2, OnRadio2)
	ON_BN_CLICKED(IDC_RADIO3, OnRadio3)
	ON_BN_CLICKED(IDC_RADIO4, OnRadio4)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


//////////////////////////////////////////////////////////////////////
//					choosetrack::OnInitDialog()
//////////////////////////////////////////////////////////////////////
// This is called when the dialog first opens.

BOOL choosetrack::OnInitDialog() 
{
	// Standard Initialization of the dialog
	CDialog::OnInitDialog();
	
	// 'remember' the old value of track in case the user presses CANCEL
	oldTrack = gV.trackChosen;
	
	return TRUE;  // return TRUE unless you set the focus to a control
}
//////////////////////////////////////////////////////////////////////



//////////////////////////////////////////////////////////////////////
// When the radio buttons are clicked, the value for track chosen
// changes accordingly.

void choosetrack::OnRadio1() 
{
	gV.trackChosen = 1;
}

void choosetrack::OnRadio2() 
{
	gV.trackChosen = 2;
}

void choosetrack::OnRadio3() 
{
	gV.trackChosen = 3;	
}

void choosetrack::OnRadio4() 
{
	gV.trackChosen = 4;	
}
//////////////////////////////////////////////////////////////////////




//////////////////////////////////////////////////////////////////////
//						choosetrack::OnCancel()
//////////////////////////////////////////////////////////////////////
// This is called when the user presses CANCEL on the dialog.

void choosetrack::OnCancel() 
{
	// Restore the old value of the track
	gV.trackChosen = oldTrack;

	// Standard Dialog canceling
	CDialog::OnCancel();
}

//////////////////////////////////////////////////////////////////////



//////////////////////////////////////////////////////////////////////
//						choosetrack::OnOK()
//////////////////////////////////////////////////////////////////////
// This is called when the user presses OK on the dialog.

void choosetrack::OnOK() 
{
	// If the play mode is capture the flag then we do not want
	// to be able to change the track.
	if (gV.playMode != 2)
	{
		double x, y;
		
		// If there is a previous track, delete it
		if (gV.mainTrack)
			delete gV.mainTrack;

		gV.drawDynamite = false;
		gV.drawGear = false;
		gV.drawMedikit = false;
		gV.drawOil = false;

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
		}
	}
	else
		gV.trackChosen = oldTrack;
	
	// Close the dialog
	CDialog::OnOK();
}

//////////////////////////////////////////////////////////////////////
