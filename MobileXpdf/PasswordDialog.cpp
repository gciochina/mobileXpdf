// PasswordDialog.cpp : implementation file
//

#include "stdafx.h"
#include "MxpdfConfig.h"
#include "MobileXpdf.h"
#include "PasswordDialog.h"
#include "SIPanel.h"


IMPLEMENT_DYNAMIC(CPasswordDialog, CDialog)

CPasswordDialog::CPasswordDialog(CWnd* pParent /*=NULL*/)
	: CDialog(CPasswordDialog::IDD, pParent)
	, m_OwnerPassword(_T(""))
{
	m_bFullScreen=FALSE;
}

CPasswordDialog::~CPasswordDialog()
{
}

void CPasswordDialog::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
    DDX_Text(pDX, IDC_OWNERPW, m_OwnerPassword);
    DDX_Control(pDX, IDC_OWNERPW, m_EditPassword);
}


BEGIN_MESSAGE_MAP(CPasswordDialog, CDialog)
    ON_EN_CHANGE(IDC_OWNERPW, &CPasswordDialog::OnEnChangeOwnerpw)
    ON_EN_SETFOCUS(IDC_OWNERPW, &CPasswordDialog::OnEnSetfocusOwnerpw)
    ON_EN_KILLFOCUS(IDC_OWNERPW, &CPasswordDialog::OnEnKillfocusOwnerpw)
END_MESSAGE_MAP()


BOOL CPasswordDialog::OnInitDialog()
{
	CDialog::OnInitDialog();

    m_EditPassword.SetFocus();

	return FALSE;   // return TRUE unless you set the focus to a control
}


// CPasswordDialog message handlers

void CPasswordDialog::OnEnChangeOwnerpw()
{
    // TODO:  If this is a RICHEDIT control, the control will not
    // send this notification unless you override the CDialog::OnInitDialog()
    // function and call CRichEditCtrl().SetEventMask()
    // with the ENM_CHANGE flag ORed into the mask.

    // TODO:  Add your control notification handler code here
}

void CPasswordDialog::OnEnSetfocusOwnerpw()
{
    // TODO: Add your control notification handler code here
#if USE_SIP
    SIPanel::getInstance().set( USE_SIP_NAME );
    SIPanel::getInstance().show();
#endif

}

void CPasswordDialog::OnEnKillfocusOwnerpw()
{
    // TODO: Add your control notification handler code here
#if USE_SIP
    SIPanel::getInstance().hide();
#endif
}
