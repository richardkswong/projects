
// MarkProtection.h : main header file for the MarkProtection application
//
#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"       // main symbols


// CMarkProtectionApp:
// See MarkProtection.cpp for the implementation of this class
//

class CMarkProtectionApp : public CWinApp
{
public:
	CMarkProtectionApp();


// Overrides
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// Implementation
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CMarkProtectionApp theApp;
