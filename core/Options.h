//////////////////////////////////////////////////////////////////////
// Tim Rudowski
// Christopher Bubeck
// Senior Project
// Due Date:  11/29/00
// NOTE:  This entire file is Visual Studio machine generated, except
// for the private section of the class
//
// Options.h declares functions for the Options dialog.
// The options dialog object derives from the MFC object CDialog.
//////////////////////////////////////////////////////////////////////


#if !defined(AFX_OPTIONS_H__7A8CA152_F67B_464A_A1B9_2991A71429A5__INCLUDED_)
#define AFX_OPTIONS_H__7A8CA152_F67B_464A_A1B9_2991A71429A5__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// Options dialog

class Options : public CDialog
{
// Construction
public:
	Options(CWnd* pParent = NULL);   // standard constructor

	// Dialog Data
	// These are the variables that are linked to the text boxes
	// in the dialog.
	//{{AFX_DATA(Options)
	enum { IDD = IDD_OPTIONS_DIALOG };
	CString	m_Player1Name;
	CString	m_Player2Name;
	short	m_LapBox;
	short	m_TimeBox;
	//}}AFX_DATA


	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(Options)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(Options)
	afx_msg void OnRadio1();
	afx_msg void OnRadio2();
	virtual void OnCancel();
	virtual void OnOK();
	afx_msg void OnRadio4();
	afx_msg void OnRadio3();
	virtual BOOL OnInitDialog();
	afx_msg void OnRadio0();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:

	int oldPlayMode;
	int oldNoPlayers;
	// These variables store the values for the old values of
	// play mode and number of players.  When CANCEL is clicked the 
	// values are returned to their old values.
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_OPTIONS_H__7A8CA152_F67B_464A_A1B9_2991A71429A5__INCLUDED_)
