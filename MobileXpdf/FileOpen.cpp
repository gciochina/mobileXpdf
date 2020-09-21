// Dialog.cpp : implementation file
//

#include "stdafx.h"
#include "MobileXpdf.h"
#include "FileOpen.h"


// CFileOps dialog

IMPLEMENT_DYNAMIC(CFileOps, CDialog)

CFileOps::CFileOps(CWnd* pParent /*=NULL*/)
: CDialog(CFileOps::IDD, pParent)
, m_lastPage(0)
, m_currentPage(0)
{
	m_bFullScreen = FALSE;

}

CFileOps::~CFileOps()
{
}

void CFileOps::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_PagesListBox);
}


BEGIN_MESSAGE_MAP(CFileOps, CDialog)
	ON_LBN_SELCHANGE(IDC_LIST1, &CFileOps::OnLbnSelchangeList1)
	ON_BN_CLICKED(IDOK, &CFileOps::OnBnClickedOk)
//	ON_WM_NCMBUTTONDOWN()
END_MESSAGE_MAP()


// CFileOps message handlers

void CFileOps::OnLbnSelchangeList1()
{
	UpdateData();
	m_lastPage = m_PagesListBox.GetCurSel();	
	m_PagesListBox.GetText(m_PagesListBox.GetCurSel(),strOpenedPath);
	TCHAR strTemp[MAX_PATH] = _T("");
	_stprintf(strTemp, _T("\\Storage Card\\%s"),strOpenedPath);
	strOpenedPath.Format(strTemp);
	
	//EndDialog(IDOK);
}

BOOL CFileOps::OnInitDialog()
{
	CDialog::OnInitDialog();
	m_PagesListBox.ResetContent();
	_File_Parser();
	m_PagesListBox.SetCurSel(m_currentPage-1);

	//selection will always be preset!
	m_PagesListBox.SetCurSel(0);

	return FALSE;
}

bool _Check_FileExtension(TCHAR strFileName[MAX_PATH])
{
	CString strTemp;
	strTemp.Format(strFileName);
	if (strTemp.Find(L".PDF") >= 0)
		return true;
	if (strTemp.Find(L".pdf") >= 0)
		return true;
	if (strTemp.Find(L".Pdf") >= 0)
		return true;
	return false;
}

int CFileOps::_File_Parser ()
{
	TCHAR strSearchPath[MAX_PATH] = _T("");
#ifdef DEBUG
	_stprintf(strSearchPath, _T("\\Storage Card"));
#else
	_stprintf(strSearchPath, _T("\\Storage Card"));
#endif
	{
		int iFilePos = -1;
		TCHAR strFileName[MAX_PATH] = _T("");
		WIN32_FIND_DATA FindFileData;
		HANDLE hFind = INVALID_HANDLE_VALUE;		
		TCHAR DirSpec[MAX_PATH] = _T(""); 
		DWORD dwError;
		_stprintf(DirSpec, _T("%s\\*"), strSearchPath);
		//strcat(DirSpec, "*", 2);
		hFind = FindFirstFile((LPCWSTR)DirSpec, &FindFileData);
		if (hFind == INVALID_HANDLE_VALUE) 
		{

			_stprintf(strFileName,_T("Invalid file handle. Error is %u"), GetLastError());
			if (_Check_FileExtension(strFileName))
				m_PagesListBox.AddString(strFileName);
			m_PagesListBox.AddString(_T("Cancel"));
			return (-1);
		} 
		else 
		{
			_stprintf(strFileName, _T("%s"), FindFileData.cFileName);
			if (_Check_FileExtension(strFileName))
				m_PagesListBox.AddString(strFileName);
			while (FindNextFile(hFind, &FindFileData) != 0) 
			{
				_stprintf(strFileName, _T("%s"), FindFileData.cFileName);
				iFilePos++;
				if (_Check_FileExtension(strFileName))
					m_PagesListBox.AddString(strFileName);
			}
			dwError = GetLastError();
			FindClose(hFind);
			if (dwError != ERROR_NO_MORE_FILES) 
			{
				_stprintf(strFileName, _T("FindNextFile error. Error is %u"), dwError);
				if (_Check_FileExtension(strFileName))
					m_PagesListBox.AddString(strFileName);
				m_PagesListBox.AddString(_T("Cancel"));
				return (-1);
			}
		}
		m_PagesListBox.AddString(_T("Cancel"));
		return (0);
	}
}

void CFileOps::OnBnClickedOk()
{	
	UpdateData();
	TCHAR strTemp[MAX_PATH] = _T("");
	if (!_tcsicmp(strTemp, _T("Cancel")))
	{//we get out !
		EndDialog(0);
	}

	//_stprintf(strTemp, _T("\\Storage Card\\%s"),strOpenedPath);
	_stprintf(strTemp, _T("%s"),strOpenedPath);
	strOpenedPath.Format(strTemp);
	OnOK();
}

BOOL CFileOps::PreTranslateMessage(MSG* pMsg) 
{
	switch (pMsg->message)
	{
	case WM_KEYDOWN:
		if (pMsg->wParam == VK_RETURN)
		{
			OnBnClickedOk();
		}
		break;
	}
	return CDialog::PreTranslateMessage(pMsg);
}


//void CFileOps::OnNcMButtonDown(UINT nHitTest, CPoint point)
//{
//	// TODO: Add your message handler code here and/or call default
//	CDialog::OnNcMButtonDown(nHitTest, point);
//}
