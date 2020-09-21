#pragma once


// CAcknowledgeDialog dialog

class CAcknowledgeDialog : public CDialog
{
	DECLARE_DYNAMIC(CAcknowledgeDialog)

public:
	CAcknowledgeDialog(CWnd* pParent = NULL);   // standard constructor
	virtual ~CAcknowledgeDialog();

// Dialog Data
	enum { IDD = IDD_ACKNOWLEDGE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	CStatic m_AcknowledgeMessage;
public:
	void setAcknowledgeMessage(CString ackmessage);
};
