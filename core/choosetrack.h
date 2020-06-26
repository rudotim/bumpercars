//////////////////////////////////////////////////////////////////////
// Tim Rudowski
// Christopher Bubeck
// Senior Project
// Due Date:  11/29/00
//
// NOTE:  This entire file is Visual Studio machine generated, except
// for the private section of the class.
//
// This declares the functions used by the Choose Track dialog.
//
// The choosetrack dialog object derives from the CDialog object.
// choosetrack is used to display the "Choose Track" dialog to the user.
//////////////////////////////////////////////////////////////////////


#if !defined(AFX_CHOOSETRACK_H__AC1D075A_07AC_49D2_AA6E_6E4E68C9BF15__INCLUDED_)
#define AFX_CHOOSETRACK_H__AC1D075A_07AC_49D2_AA6E_6E4E68C9BF15__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// choosetrack.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// choosetrack dialog

class choosetrack : public CDialog
{
// Construction
public:
	choosetrack(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(choosetrack)
	enum { IDD = IDD_CHOOSETRACK_DIALOG };
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(choosetrack)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(choosetrack)
	afx_msg void OnRadio1();
	afx_msg void OnRadio2();
	virtual void OnCancel();
	afx_msg void OnRadio3();
	afx_msg void OnRadio4();
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:

	int oldTrack;
	// This variable stores the value for the old value of
	// the track.  When CANCEL is clicked the track value is returned to
	// its old value.

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CHOOSETRACK_H__AC1D075A_07AC_49D2_AA6E_6E4E68C9BF15__INCLUDED_)
