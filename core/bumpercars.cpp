//////////////////////////////////////////////////////////////////////
// Tim Rudowski
// Christopher Bubeck
// Senior Project
// Due Date:  11/29/00
// NOTE:  This entire file is Visual Studio machine generated...
//
// bumpercars.cpp : Defines the class behaviors for the application.
//
// The MFC start-up wizard generates a simple application class from
// which we built upon.  The application class works to call the main
// dialog.  When the main dialog exits, then the application process
// exits and the program ends.
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "bumpercars.h"
#include "bumpercarsDlg.h"
#include "functions.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


/////////////////////////////////////////////////////////////////////////////
// CBumpercarsApp

BEGIN_MESSAGE_MAP(CBumpercarsApp, CWinApp)
	//{{AFX_MSG_MAP(CBumpercarsApp)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG
	ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CBumpercarsApp construction

CBumpercarsApp::CBumpercarsApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CBumpercarsApp object

CBumpercarsApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CBumpercarsApp initialization

BOOL CBumpercarsApp::InitInstance()
{
	AfxEnableControlContainer();

	// Standard initialization
	// If you are not using these features and wish to reduce the size
	//  of your final executable, you should remove from the following
	//  the specific initialization routines you do not need.

#ifdef _AFXDLL
	Enable3dControls();			// Call this when using MFC in a shared DLL
#else
	Enable3dControlsStatic();	// Call this when linking to MFC statically
#endif

	CBumpercarsDlg dlg;
	m_pMainWnd = &dlg;

	// DoModal() is the function which actually opens the dialog
	dlg.DoModal();

	// Since the dialog has been closed, return FALSE so that we exit the
	//  application, rather than start the application's message pump.
	return FALSE;
}
