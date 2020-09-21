#pragma once
#include "afxwin.h"


// CPasswordDialog dialog

class CPasswordDialog : public CDialog
{
	DECLARE_DYNAMIC(CPasswordDialog)

public:
	CPasswordDialog(CWnd* pParent = NULL);   // standard constructor
	virtual ~CPasswordDialog();

    virtual BOOL OnInitDialog();

// Dialog Data
	enum { IDD = IDD_PASSWORD };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	CString m_OwnerPassword;
    afx_msg void OnEnChangeOwnerpw();
    afx_msg void OnEnSetfocusOwnerpw();
    afx_msg void OnEnKillfocusOwnerpw();
    CEdit m_EditPassword;
};
