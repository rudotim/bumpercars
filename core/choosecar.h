//////////////////////////////////////////////////////////////////////
// Tim Rudowski
// Christopher Bubeck
// Senior Project
// Due Date:  11/29/00
//
// choosecar.h declares the functions used by the Choose Car dialog.
//
// The choosecar also derives from the MFC object CDialog.
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CHOOSECAR_H__BC8C0666_8283_4372_829E_B7EFCA5BDFD4__INCLUDED_)
#define AFX_CHOOSECAR_H__BC8C0666_8283_4372_829E_B7EFCA5BDFD4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// choosecar dialog

class choosecar : public CDialog
{
// Construction
public:
	choosecar(CWnd* pParent = NULL);   // standard constructor

	// Dialog Data
	// These are the variables that are linked to the static text boxes
	// in the dialog.
	//{{AFX_DATA(choosecar)
	enum { IDD = IDD_CHOOSECAR_DIALOG };
	CString	m_Player1Car;
	CString	m_Player2Car;
	//}}AFX_DATA


	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(choosecar)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(choosecar)
	afx_msg void OnPlayer1();
	afx_msg void OnPlayer2();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CHOOSECAR_H__BC8C0666_8283_4372_829E_B7EFCA5BDFD4__INCLUDED_)
