
// HightDpi.h : main header file for the HightDpi application
//
#pragma once

#ifndef __AFXWIN_H__
	#error "include 'pch.h' before including this file for PCH"
#endif

#include "resource.h"       // main symbols


// CHightDpiApp:
// See HightDpi.cpp for the implementation of this class
//

class CHightDpiApp : public CWinApp
{
public:
	CHightDpiApp() noexcept;


// Overrides
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// Implementation
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CHightDpiApp theApp;
