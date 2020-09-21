#pragma once
#include "afxwin.h"
#include "NumEdit.h"


// CGotoPageDialog dialog

class CGotoPageDialog : public CDialog
{
	DECLARE_DYNAMIC(CGotoPageDialog)

public:
	CGotoPageDialog(CWnd* pParent = NULL);   // standard constructor
	virtual ~CGotoPageDialog();

// Dialog Data
	enum { IDD = IDD_GOTOPAGE };

    int mCurrentPage;
    int mNumOfPages;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
    afx_msg void OnEnChangeEdit1();
    afx_msg void OnEnSetfocusEdit1();
    afx_msg void OnEnKillfocusEdit1();

    CNumEdit mEditPageNum;
    afx_msg void OnEnChangeEditpagenum();
    virtual BOOL OnInitDialog();
    CString mPageNumberStr;
};
