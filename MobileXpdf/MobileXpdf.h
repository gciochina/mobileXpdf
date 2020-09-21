// MobileXpdf.h : main header file for the MobileXpdf application
//
#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resourceppc.h"

// CMobileXpdfApp:
// See MobileXpdf.cpp for the implementation of this class
//

class CMobileXpdfApp : public CWinApp
{
public:
	CMobileXpdfApp();

// Overrides
public:
	virtual BOOL InitInstance();

// Implementation
public:
	afx_msg void OnAppAbout();

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnMenuQuit();
public:
	virtual int ExitInstance();
public:
	void CheckForRunningInstance(void);
};

void SetCBSize(CComboBox & cb, int max_items);
extern CMobileXpdfApp theApp;
