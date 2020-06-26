//////////////////////////////////////////////////////////////////////
// Tim Rudowski
// Christopher Bubeck
// Senior Project
// Due Date:  11/29/00
// NOTE:  This entire file is Visual Studio machine generated...
//
// This provides the definitions for the main Bumper Cars menu.
//
// The main dialog derives from the MFC object CDialog, as do many
// of the other dialogs used in this game.
//////////////////////////////////////////////////////////////////////
//
//{{AFX_INCLUDES()
#include "commandbutton.h"
#include "playcontrol1.h"
//}}AFX_INCLUDES

#if !defined(AFX_BUMPERCARSDLG_H__774A455D_DE80_4471_9A50_4F16001AA6A4__INCLUDED_)
#define AFX_BUMPERCARSDLG_H__774A455D_DE80_4471_9A50_4F16001AA6A4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CBumpercarsDlg dialog

class CBumpercarsDlg : public CDialog
{
// Construction
public:
	CBumpercarsDlg(CWnd* pParent = NULL);	// standard constructor

	// Dialog Data
	// These variables correspond to the buttons that are pressed
	// on the main menu, e.g. "PLAY", "MULTIPLAYER", etc.
	//{{AFX_DATA(CBumpercarsDlg)
	enum { IDD = IDD_BUMPERCARS_DIALOG };
	CButton	m_Button1;
	CCommandButton	m_Command2;
	CCommandButton	m_ExitCommand;
	CCommandButton	m_PlayCommand;
	CCommandButton	m_ChooseCar;
	CCommandButton	m_ChooseTrack;
	CCommandButton	m_Multiplayer;
	CCommandButton	m_Options;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CBumpercarsDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CBumpercarsDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnClickExit();
	afx_msg void OnClickPlay();
	afx_msg void OnClickMultiplayer();
	afx_msg void OnClickChooseTrack();
	afx_msg void OnClickChooseCar();
	afx_msg void OnClickOptions();
	afx_msg void OnClose();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnHelpButton();
	DECLARE_EVENTSINK_MAP()
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
	// These are our counter variables for the timer
	int counterMedikit;
	int counterGear;
	int counterOil;
	int counterDynamite;

	int captureFlagCounter;

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_BUMPERCARSDLG_H__774A455D_DE80_4471_9A50_4F16001AA6A4__INCLUDED_)
