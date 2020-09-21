#pragma once
#include "NumEdit.h"
#include "AboutDialog.h"
#include "afxext.h"


// CMenuToolbarDlg dialog

class CMenuToolbarDlg : public CDialog
{
	DECLARE_DYNAMIC(CMenuToolbarDlg)

public:
	CMenuToolbarDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CMenuToolbarDlg();
	virtual int Create( UINT nIDTemplate, CWnd *pParentWnd = 0 );

// Dialog Data
	enum { IDD = IDD_MENUTOOLBAR };
    void SetPageNum( int currentPage, int numofPages );

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	CBitmap			mBackground;
	CBrush			mBrushLabelFilename;
	CBrush			mBrushLabelPageCount;
	CBrush			mBrushEdit;
	CSize			mBitmapSize;
	//CFont			mFont;

	CBitmapButton	mButtonClose;
	CBitmapButton	mButtonPrev;
	CBitmapButton	mButtonNext;
	CBitmapButton	mButtonAbout;
	CStatic			*mLabelFilename;
	CStatic			*mLabelPageNumber;
	CNumEdit		mEditPageNumber;

    int             mDocCurrentPage;
    int             mDocNumOfPages;

	CAboutDialog	mAboutDlg;

// Implementation
protected:
	virtual BOOL OnInitDialog();

	DECLARE_MESSAGE_MAP()
public:
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnDestroy();
	afx_msg void OnClose();
	afx_msg void OnActivate(UINT nState, CWnd* pWndOther, BOOL bMinimized);
	afx_msg void OnPrevPage();
	afx_msg void OnNextPage();
	afx_msg void OnBnClickedAbout();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
 
	void setCaption(LPWSTR text);
	void enableButtonPrev(BOOL state);
	void enableButtonNext(BOOL state);
    virtual BOOL PreTranslateMessage(MSG* pMsg);
};
