#pragma once


// CAboutDialog dialog

class CAboutDialog : public CDialog
{
	DECLARE_DYNAMIC(CAboutDialog)

public:
	CAboutDialog(CWnd* pParent = NULL);   // standard constructor
	virtual ~CAboutDialog();

// Dialog Data
	enum { IDD = IDD_ABOUTDIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
};
