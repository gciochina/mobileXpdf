// AcknowledgeDialog.cpp : implementation file
//

#include "stdafx.h"
#include "MobileXpdf.h"
#include "AcknowledgeDialog.h"


// CAcknowledgeDialog dialog

IMPLEMENT_DYNAMIC(CAcknowledgeDialog, CDialog)

CAcknowledgeDialog::CAcknowledgeDialog(CWnd* pParent /*=NULL*/)
	: CDialog(CAcknowledgeDialog::IDD, pParent)
{

}

CAcknowledgeDialog::~CAcknowledgeDialog()
{
}

void CAcknowledgeDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_ACKNOWLEDGEMSG, m_AcknowledgeMessage);
}


BEGIN_MESSAGE_MAP(CAcknowledgeDialog, CDialog)
END_MESSAGE_MAP()


// CAcknowledgeDialog message handlers

void CAcknowledgeDialog::setAcknowledgeMessage(CString ackmessage)
{
	m_AcknowledgeMessage.SetWindowTextW(ackmessage);
	m_AcknowledgeMessage.Invalidate();
}