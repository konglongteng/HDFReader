// HDFTest.h : main header file for the HDFTEST application
//

#if !defined(AFX_HDFTEST_H__B3775D5B_7DE8_4EF4_9F9E_49B24EBBFAFB__INCLUDED_)
#define AFX_HDFTEST_H__B3775D5B_7DE8_4EF4_9F9E_49B24EBBFAFB__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CHDFTestApp:
// See HDFTest.cpp for the implementation of this class
//

class CHDFTestApp : public CWinApp
{
public:
	CHDFTestApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CHDFTestApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CHDFTestApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_HDFTEST_H__B3775D5B_7DE8_4EF4_9F9E_49B24EBBFAFB__INCLUDED_)
