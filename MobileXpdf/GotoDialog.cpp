// GotoDialog.cpp : implementation file
//

#include "stdafx.h"
#include "MobileXpdf.h"
#include "GotoDialog.h"


// CGotoDialog dialog

IMPLEMENT_DYNAMIC(CGotoDialog, CDialog)

CGotoDialog::CGotoDialog(CWnd* pParent /*=NULL*/)
	: CDialog(CGotoDialog::IDD, pParent)
	, m_lastPage(0)
	, m_currentPage(0)
{
	m_bFullScreen = FALSE;

}

CGotoDialog::~CGotoDialog()
{
}

void CGotoDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_PagesListBox);
}


BEGIN_MESSAGE_MAP(CGotoDialog, CDialog)
	ON_LBN_SELCHANGE(IDC_LIST1, &CGotoDialog::OnLbnSelchangeList1)
//	ON_BN_CLICKED(IDCANCEL, &CGotoDialog::OnBnClickedCancel)
	ON_BN_CLICKED(IDOK, &CGotoDialog::OnBnClickedOk)
END_MESSAGE_MAP()


// CGotoDialog message handlers

void CGotoDialog::OnLbnSelchangeList1()
{
	UpdateData();
	m_lastPage = m_PagesListBox.GetCurSel();
	//OnOK();
	//EndDialog(IDOK);
}

BOOL CGotoDialog::OnInitDialog()
{
	CDialog::OnInitDialog();

	m_PagesListBox.ResetContent();
	for (int i = 1; i<=m_lastPage;i++){
		wchar_t str[10];
		wsprintf(str,L"Page %d",i);
		m_PagesListBox.AddString(str);
	}
	m_PagesListBox.SetCurSel(m_currentPage-1);

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}
// void CGotoDialog::OnBnClickedCancel()
// {
// 	// TODO: Add your control notification handler code here
// 	OnCancel();
// }

void CGotoDialog::OnBnClickedOk()
{
	UpdateData();
	m_lastPage = m_PagesListBox.GetCurSel();
	// TODO: Add your control notification handler code here
	OnOK();
}
