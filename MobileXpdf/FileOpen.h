#pragma once
#include "afxcmn.h"
#include "afxwin.h"


// CFileOps dialog

class CFileOps : public CDialog
{
	DECLARE_DYNAMIC(CFileOps)

public:
	CFileOps(CWnd* pParent = NULL);   // standard constructor
	virtual ~CFileOps();
 
	// Dialog Data
	enum { IDD = IDD_FILE_OPEN };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	CString strOpenedPath;
public:
	CListBox m_PagesListBox;
public:
	afx_msg void OnLbnSelchangeList1();
public:
	virtual BOOL OnInitDialog();
public:
	int m_lastPage;
public:
	int m_currentPage;
public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	int _File_Parser ();
	afx_msg void OnBnClickedOk();	
};
