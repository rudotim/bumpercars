//////////////////////////////////////////////////////////////////////
// Tim Rudowski
// Christopher Bubeck
// Senior Project
// Due Date:  11/29/00
//
// Multiplayer.h declares the functions used to run Bumper Cars
// multiplayer sessions.
//
//////////////////////////////////////////////////////////////////////

//{{AFX_INCLUDES()
#include "playcontrol1.h"
//}}AFX_INCLUDES
#if !defined(AFX_MULTIPLAYER_H__9C9BAB99_41BD_4DE9_A306_5E9864F35605__INCLUDED_)
#define AFX_MULTIPLAYER_H__9C9BAB99_41BD_4DE9_A306_5E9864F35605__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Multiplayer.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// Multiplayer dialog

class Multiplayer : public CDialog
{
// Construction
public:
	Multiplayer(CWnd* pParent = NULL);   // standard constructor
	void Receive();			// used to recieve messages

	// Dialog Data
	// These values correspond to the different text boxes, the chat
	// window, and the static text boxes on the dialog.
	//{{AFX_DATA(Multiplayer)
	enum { IDD = IDD_MULTIPLAYER };
	CEdit	m_EditMessage;
	CButton	m_StartGame;
	CButton	m_Send;
	CButton	m_Join;
	CButton	m_Create;
	CListBox	m_ChatBox;
	CPlayControl	m_DirectPlay;
	CString	m_Message;
	int		m_Connected;
	CString	m_MPlayerName1;
	CString	m_MPlayerName2;
	CString	m_MPlayerTrack;
	CString	m_MPlayerNo;
	CString	m_MPlayerMode;
	//}}AFX_DATA


	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(Multiplayer)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(Multiplayer)
	afx_msg void OnCreate();
	afx_msg void OnJoin();
	afx_msg void OnPositionMessageReceived();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnStartGame();
	afx_msg void OnSend();
	virtual BOOL OnInitDialog();
	afx_msg void OnNumberPlayersChanged();
	afx_msg void OnStartMessageReceived();
	afx_msg void OnChatMessageReceived();
	afx_msg void OnBumpMessageReceived();
	afx_msg void OnWinnerMessageReceived();
	afx_msg void OnDrawMessageReceived();
	afx_msg void OnUnDrawMessageReceived();
	afx_msg void OnAcquireMessageReceived();
	afx_msg void OnUnAcquireMessageReceived();
	afx_msg void OnIPX();
	afx_msg void OnTCPIP();
	virtual void OnCancel();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:

	// These are variables used to temporarily store information, like
	// the connection type, an old message (see OnChatMessageReceived() )
	// and whether or not we have already started a session.
	bool alreadyStarted;
	CString oldMessage;
	short Connection;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MULTIPLAYER_H__9C9BAB99_41BD_4DE9_A306_5E9864F35605__INCLUDED_)
