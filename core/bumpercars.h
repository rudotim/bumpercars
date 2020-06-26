//////////////////////////////////////////////////////////////////////
// Tim Rudowski
// Christopher Bubeck
// Senior Project
// Due Date:  11/29/00
// NOTE:  This entire file (except for gameVariables struct) 
// is Visual Studio machine generated...
//
// bumpercars.h : main header file for the BUMPERCARS application
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_BUMPERCARS_H__7A47DABA_157F_4A2F_8B30_24434D3C0130__INCLUDED_)
#define AFX_BUMPERCARS_H__7A47DABA_157F_4A2F_8B30_24434D3C0130__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols
#include "track.h"

/////////////////////////////////////////////////////////////////////////////
// CBumpercarsApp:
// See bumpercars.cpp for the implementation of this class
//

class CBumpercarsApp : public CWinApp
{
public:
	CBumpercarsApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CBumpercarsApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CBumpercarsApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


// Here we define a struct containing variables for game play.
// These variables are shared among the different .cpp files of the
// application.

typedef struct _gameVariables
{
	bool canCapture;			//if this is true, then the flag is up for grabs,
								//otherwise, a car has it
	bool drawMedikit;			//true if medikit is on screen
	bool drawGear;				//true if gear is on screen
	bool drawOil;				//true if oil slick is on screen
	bool drawDynamite;			//true if there is dynamite on screen
	bool multiplayerEnabled;	//is this multiplayer?
	int trackChosen;			//the number of the track chosen
	bool twoPlayers;			//do we have 2 players locally?
	int localPlayers;			//number of local players
	int totalPlayers;			//number of players on all machines combined
	int localCar[2];			//array of two values
	short numberOfLaps;			//number of laps to be completed in race mode
	CString playerNames[4];		//array of player names
	long playerIDs[2];			//DirectPlay player ID #s
	int playMode;				//the play mode we are in
	short timeLimit;			//time limit for capture the flag
	short winner;				//number of person who has won the game
	int whoHasFlag;				//keep track of who has the flag
	Track * mainTrack;			//a pointer to the track we are using

} gameVariables;


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_BUMPERCARS_H__7A47DABA_157F_4A2F_8B30_24434D3C0130__INCLUDED_)
