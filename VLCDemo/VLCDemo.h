// VLCDemo.h : main header file for the VLCDEMO application
//

#if !defined(AFX_VLCDEMO_H__0D36E245_3DE8_48FD_B0B2_50DBE470835E__INCLUDED_)
#define AFX_VLCDEMO_H__0D36E245_3DE8_48FD_B0B2_50DBE470835E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CVLCDemoApp:
// See VLCDemo.cpp for the implementation of this class
//

class CVLCDemoApp : public CWinApp
{
public:
	CVLCDemoApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CVLCDemoApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CVLCDemoApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_VLCDEMO_H__0D36E245_3DE8_48FD_B0B2_50DBE470835E__INCLUDED_)
