// GotoPageDialog.cpp : implementation file
//

#include "stdafx.h"
#include "MobileXpdf.h"
#include "GotoPageDialog.h"


// CGotoPageDialog dialog

IMPLEMENT_DYNAMIC(CGotoPageDialog, CDialog)

CGotoPageDialog::CGotoPageDialog(CWnd* pParent /*=NULL*/)
	: CDialog(CGotoPageDialog::IDD, pParent), mCurrentPage( 0 ), mNumOfPages( 0 )
    , mPageNumberStr(_T(""))
{
}

CGotoPageDialog::~CGotoPageDialog()
{
}

void CGotoPageDialog::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_EDITPAGENUM, mEditPageNum);
    DDX_Text(pDX, IDC_EDITPAGENUM, mPageNumberStr);
}


BEGIN_MESSAGE_MAP(CGotoPageDialog, CDialog)
    ON_EN_CHANGE(IDC_EDIT1, &CGotoPageDialog::OnEnChangeEdit1)
    ON_EN_SETFOCUS(IDC_EDIT1, &CGotoPageDialog::OnEnSetfocusEdit1)
    ON_EN_KILLFOCUS(IDC_EDIT1, &CGotoPageDialog::OnEnKillfocusEdit1)
    //ON_EN_CHANGE(IDC_EDITPAGENUM, &CGotoPageDialog::OnEnChangeEditpagenum)
END_MESSAGE_MAP()


// CGotoPageDialog message handlers

void CGotoPageDialog::OnEnChangeEdit1()
{
    // TODO:  If this is a RICHEDIT control, the control will not
    // send this notification unless you override the CDialog::OnInitDialog()
    // function and call CRichEditCtrl().SetEventMask()
    // with the ENM_CHANGE flag ORed into the mask.

    // TODO:  Add your control notification handler code here
}

void CGotoPageDialog::OnEnSetfocusEdit1()
{
    // TODO: Add your control notification handler code here
}

void CGotoPageDialog::OnEnKillfocusEdit1()
{
    // TODO: Add your control notification handler code here
}

void CGotoPageDialog::OnEnChangeEditpagenum()
{
    // TODO:  If this is a RICHEDIT control, the control will not
    // send this notification unless you override the CDialog::OnInitDialog()
    // function and call CRichEditCtrl().SetEventMask()
    // with the ENM_CHANGE flag ORed into the mask.

    // TODO:  Add your control notification handler code here
}

BOOL CGotoPageDialog::OnInitDialog()
{
    CDialog::OnInitDialog();

    // TODO:  Add extra initialization here
    mEditPageNum.SetMinMax( 1, mNumOfPages );   
    mEditPageNum.SetFocus();

    return FALSE;  // return TRUE unless you set the focus to a control
    // EXCEPTION: OCX Property Pages should return FALSE
}
