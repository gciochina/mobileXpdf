// ConfigDialog.cpp : implementation file
//

#include "stdafx.h"
#include "MobileXpdf.h"
#include "MxpdfConfig.h"
#include "ConfigDialog.h"
#include "ButtonGrabberDialog.h"

#ifdef USE_CUSTOM_KEY_CODES
#include "CustomKeyCodes.h"
#endif

// CConfigDialog dialog

IMPLEMENT_DYNAMIC(CConfigDialog, CDialog)

CConfigDialog::CConfigDialog(CWnd* pParent /*=NULL*/)
	: CDialog(CConfigDialog::IDD, pParent)
	, m_AntiAliasing(FALSE)
	, m_MapHWButtons(FALSE)
	, m_FileAssoc(FALSE)
	, m_HideScrollbars(FALSE)
{

	CWinApp* pApp = AfxGetApp();
	m_AntiAliasing = pApp->GetProfileInt(L"Xpdf",L"AntiAliasing",1);
	m_MapHWButtons = pApp->GetProfileInt(L"Xpdf",L"MapHWButtons",0);
	m_HideScrollbars = pApp->GetProfileInt(L"Xpdf",L"HideScrollbars",0);

#ifdef USE_CUSTOM_KEY_CODES
	const int NUMDEFAULTMAPPINGS=10;
	ButtonMapping defaultmappings[NUMDEFAULTMAPPINGS] = {
		{KEY02,PRIORSCREEN},
		{KEY05,PRIORSCREEN},
		{KEY06,PRIORSCREEN},
		{KEY04,NEXTSCREEN},
		{KEY07,NEXTSCREEN},
		{KEY08,NEXTSCREEN},
		{KEY01,LEFTSCREEN},
		{KEY03,RIGHTSCREEN},
		{KEY09,ZOOMIN},
		{KEY10,ZOOMOUT},

	};
#else
	const int NUMDEFAULTMAPPINGS=6;
	ButtonMapping defaultmappings[NUMDEFAULTMAPPINGS] = {
		{VK_UP,PRIORSCREEN},
		{VK_DOWN,NEXTSCREEN},
		{VK_LEFT,LEFTSCREEN},
		{VK_RIGHT,RIGHTSCREEN},
		{VK_RETURN,NEXTPAGE},
		{VK_F10,PREVPAGE},

	};
#endif

	ButtonMapping none = {-1,NONE};
	
	for (int i=0;i<MAXMAPPINGS;i++)
	{
		/*CString name;
		name.Format(L"Mapping%d",i);
		CString mapping = pApp->GetProfileString(L"Xpdf",name,L"");
		if (mapping==L"")
		{*/
			if (i<NUMDEFAULTMAPPINGS)
			{
				m_ButtonMappings[i]=defaultmappings[i];
			} else
			{
				m_ButtonMappings[i]=none;
			}
		/*} else
		{
			wchar_t *stopstring;
			int delim = mapping.Find(L"|");
			m_ButtonMappings[i].button=wcstol(mapping.Left(delim),&stopstring,10);
			m_ButtonMappings[i].function=(Functions)wcstol(mapping.Right(mapping.GetLength()-delim-1),&stopstring,10);
		}*/
	}
}

CConfigDialog::~CConfigDialog()
{
	CWinApp* pApp = AfxGetApp();
	
	pApp->WriteProfileInt(L"Xpdf",L"AntiAliasing",m_AntiAliasing);
	
	pApp->WriteProfileInt(L"Xpdf",L"MapHWButtons",m_MapHWButtons);

	pApp->WriteProfileInt(L"Xpdf",L"HideScrollbars",m_HideScrollbars);


	/*for (int i=0;i<MAXMAPPINGS;i++)
	{
		if (m_ButtonMappings[i].button==-1)
		{
			break;
		}
		
		CString name;
		name.Format(L"Mapping%d",i);
		CString mapping;
		mapping.Format(L"%d|%d",m_ButtonMappings[i].button,m_ButtonMappings[i].function);
		pApp->WriteProfileString(L"Xpdf",name,mapping);
	}*/
}

void CConfigDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Check(pDX, IDC_ANTIALIASING, m_AntiAliasing);
	DDX_Check(pDX, IDC_MAPHWBUTTONS, m_MapHWButtons);
	DDX_Control(pDX, IDC_MAPFUNCTION, m_MapFunctionBox);
	DDX_Control(pDX, IDC_MAPBUTTONS, m_MapButtonBox);
	DDX_Check(pDX, IDC_FILEASSOC, m_FileAssoc);
	DDX_Check(pDX, IDC_HIDESCROLLBARS, m_HideScrollbars);
	DDX_Control(pDX, IDC_SPIN, m_spinCtrl);
}


BEGIN_MESSAGE_MAP(CConfigDialog, CDialog)
	ON_CBN_SELCHANGE(IDC_MAPBUTTONS, &CConfigDialog::OnCbnSelchangeMapbuttons)
	ON_CBN_SELCHANGE(IDC_MAPFUNCTION, &CConfigDialog::OnCbnSelchangeMapfunction)
	ON_BN_CLICKED(IDOK, &CConfigDialog::OnBnClickedOk)
	ON_BN_CLICKED(IDC_MAPHWBUTTONS, &CConfigDialog::OnToggleMapHWButtons)
	ON_BN_CLICKED(IDC_SELECTBUTTON, &CConfigDialog::OnBnClickedSelectbutton)
	ON_BN_CLICKED(IDCANCEL, &CConfigDialog::OnBnClickedCancel)
	ON_BN_CLICKED(IDC_REMEMBER_ZOOM, &CConfigDialog::OnBnClickedRememberZoom)
	ON_BN_CLICKED(IDC_FILEASSOC, &CConfigDialog::OnBnClickedFileassoc)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN, &CConfigDialog::OnDeltaposSpin)
	ON_EN_CHANGE(IDC_ZOOM, &CConfigDialog::OnEnChangeZoom)
END_MESSAGE_MAP()


// CConfigDialog message handlers

BOOL CConfigDialog::OnInitDialog()
{
	
	HKEY key;
	/*if (RegOpenKeyEx(HKEY_CLASSES_ROOT,L"xpdffile\\Shell\\Open\\Command",0,KEY_QUERY_VALUE,&key)==ERROR_SUCCESS){
		wchar_t str[256];
		DWORD size=512;
		DWORD type=REG_SZ;
		ZeroMemory(str,512);
		RegQueryValueEx(key,0,0,&type,(BYTE*)str,&size);
		RegCloseKey(key);
		CString val(str);

		TCHAR szExe[MAX_PATH];
		::GetModuleFileName(NULL, szExe, MAX_PATH); 
		TCHAR value[MAX_PATH+10];
		wsprintf(value,L"\"%s\" \"%%1\"",szExe);

		m_FileAssoc=(val.Compare(value)==0);
	}*/
	if (RegOpenKeyEx(HKEY_CLASSES_ROOT,L".pdf",0,KEY_QUERY_VALUE,&key)==ERROR_SUCCESS)
	{
		wchar_t str[256];
		DWORD size=512;
		DWORD type=REG_SZ;
		ZeroMemory(str,512);
		RegQueryValueEx(key,0,0,&type,(BYTE*)str,&size);
		RegCloseKey(key);

		CString val(str);
		TCHAR szExe[MAX_PATH];
		::GetModuleFileName(NULL, szExe, MAX_PATH); 
		TCHAR value[MAX_PATH+10];
		wsprintf(value,L"xpdffile",szExe);

		m_FileAssoc=(val.Compare(value)==0);
	}
	LoadZoomSettings();

	
	
	
	CDialog::OnInitDialog();

	for (int i = 0; i<MAXMAPPINGS; i++){
		m_LocalButtonMappings[i] = m_ButtonMappings[i];
	}

	setupButtons();
	m_MapFunctionBox.AddString(L"None");
	m_MapFunctionBox.AddString(L"Next Page");
	m_MapFunctionBox.AddString(L"Prev Page");
	m_MapFunctionBox.AddString(L"Scroll Up");
	m_MapFunctionBox.AddString(L"Smartscroll Up");
	m_MapFunctionBox.AddString(L"Scroll Down");
	m_MapFunctionBox.AddString(L"Smartscroll Down");
	m_MapFunctionBox.AddString(L"Scroll Left");
	m_MapFunctionBox.AddString(L"Smartscroll Left");
	m_MapFunctionBox.AddString(L"Scroll Right");
	m_MapFunctionBox.AddString(L"Smartscroll Right");
	m_MapFunctionBox.AddString(L"Zoom in");
	m_MapFunctionBox.AddString(L"Zoom out");
	m_MapFunctionBox.AddString(L"Fit to Width");
	m_MapFunctionBox.AddString(L"Fit to Height");
	m_MapFunctionBox.AddString(L"Toggle Fullscreen");
	m_MapFunctionBox.AddString(L"Find Text");
	m_MapFunctionBox.AddString(L"Find Next");
	m_MapFunctionBox.AddString(L"Find Prior");
	m_MapFunctionBox.AddString(L"Show Outline");

	//Done-Button for Smartphone 
	SHINITDLGINFO shidi;
	ZeroMemory(&shidi, sizeof(SHINITDLGINFO));
	shidi.dwMask = SHIDIM_FLAGS;
	shidi.dwFlags = SHIDIF_DONEBUTTON | SHIDIF_SIPDOWN | SHIDIF_SIZEDLGFULLSCREEN | SHIDIF_EMPTYMENU;
	shidi.hDlg = m_hWnd;
	::SetForegroundWindow(m_hWnd);
	AYGSHELL::SHInitDialog(&shidi);

	m_spinCtrl.SetBuddy(GetDlgItem(IDC_ZOOM));
	m_spinCtrl.SetRange(100, 500);
	m_spinCtrl.SetPos(zoomLevel);

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}


void CConfigDialog::OnCbnSelchangeMapbuttons()
{
	int button = m_MapButtonBox.GetItemData(m_MapButtonBox.GetCurSel());
	int i;
	for (i = 0; i<MAXMAPPINGS; i++)
	{
		
		if (m_LocalButtonMappings[i].button==button)
		{
			m_MapFunctionBox.SetCurSel(m_LocalButtonMappings[i].function);
			return;
		} 
		if (m_LocalButtonMappings[i].button==-1)
		{
			//Add new mapping entry
			m_LocalButtonMappings[i].button=button;
			m_MapFunctionBox.SetCurSel(m_LocalButtonMappings[i].function);
			return;
		}

	}
	
}

void CConfigDialog::OnCbnSelchangeMapfunction()
{
	int button = m_MapButtonBox.GetItemData(m_MapButtonBox.GetCurSel());
	int function = m_MapFunctionBox.GetCurSel();

	for (int i = 0; i<MAXMAPPINGS; i++)
	{
		if (m_LocalButtonMappings[i].button==button)
		{
			m_LocalButtonMappings[i].function = (Functions) function;
		}
	}
	
}

void CConfigDialog::OnOK()
{
	for (int i = 0; i<MAXMAPPINGS; i++){
		m_ButtonMappings[i] = m_LocalButtonMappings[i];
	}
	UpdateData();
	if (m_FileAssoc){
		// Set file association
		DWORD dwDisp;
		HKEY key1;
		RegCreateKeyEx(HKEY_CLASSES_ROOT,L".pdf",0, NULL, REG_OPTION_NON_VOLATILE,KEY_SET_VALUE, NULL, &key1, &dwDisp);
		RegSetValueEx(key1,0,0,REG_SZ,(BYTE*)L"xpdffile",18);
		RegCloseKey(key1);
		RegCreateKeyEx(HKEY_CLASSES_ROOT,L"xpdffile\\Shell\\Open\\Command",0, NULL, REG_OPTION_NON_VOLATILE,KEY_SET_VALUE, NULL, &key1, &dwDisp);
		TCHAR szExe[MAX_PATH];
		int size = ::GetModuleFileName(NULL, szExe, MAX_PATH); 
		TCHAR *value=new TCHAR[size+7+1];
		wsprintf(value,L"\"%s\" \"%%1\"",szExe);
		if (RegSetValueEx(key1,0,0,REG_SZ,(BYTE*)value,(size+7+1)*2)!=ERROR_SUCCESS){
			MessageBox(L"Cannot write path");
		}
		RegCloseKey(key1);
		RegCreateKeyEx(HKEY_CLASSES_ROOT,L"xpdffile\\Shell\\OpenDoc\\Command",0, NULL, REG_OPTION_NON_VOLATILE,KEY_SET_VALUE, NULL, &key1, &dwDisp);
		if (RegSetValueEx(key1,0,0,REG_SZ,(BYTE*)value,(size+7+1)*2)!=ERROR_SUCCESS){
			MessageBox(L"Cannot write path");
		}
		RegCloseKey(key1);

		//Set file icon
		RegCreateKeyEx(HKEY_CLASSES_ROOT,L"xpdffile\\DefaultIcon",0, NULL, REG_OPTION_NON_VOLATILE,KEY_SET_VALUE, NULL, &key1, &dwDisp);
		
//		TCHAR *pLastSlash = _tcsrchr(szExe, _T('\\'));
//		_tcscpy(pLastSlash, _T("\\XpdfFile.ico")); 

		wsprintf(value,L"%s,-142",szExe);
		if (RegSetValueEx(key1,0,0,REG_SZ,(BYTE*)value,(_tcsclen(value))*2)!=ERROR_SUCCESS){
			MessageBox(L"Cannot write path");
		}
		RegCloseKey(key1);

		delete value;

	} else {
		DWORD dwDisp;
		HKEY key1;
		RegCreateKeyEx(HKEY_CLASSES_ROOT,L".pdf",0, NULL, REG_OPTION_NON_VOLATILE,KEY_SET_VALUE, NULL, &key1, &dwDisp);
		RegSetValueEx(key1,0,0,REG_SZ,(BYTE*)L"pdffile",16);
		RegCloseKey(key1);
	}

	/*HKEY key1;
	if (RegCreateKeyEx(HKEY_LOCAL_MACHINE,L"System\\GWE\\Commctrl",0, NULL, REG_OPTION_NON_VOLATILE,KEY_SET_VALUE, NULL, &key1, NULL)!=ERROR_SUCCESS){
			MessageBox(L"Cannot open delay key");
	}
	if (m_ContextMenuDelay){
		DWORD value = 1;
		if (RegSetValueEx(key1,L"UseLongDelayForGestures",0,REG_DWORD,(BYTE*)&value,4)!=ERROR_SUCCESS){
			MessageBox(L"Cannot set delay value");
		}
	}
	else{
		DWORD value = 0;
		if (RegSetValueEx(key1,L"UseLongDelayForGestures",0,REG_DWORD,(BYTE*)&value,4)!=ERROR_SUCCESS){
			MessageBox(L"Cannot set delay value");
		}
	}*/

	SaveZoomSettings();

	CDialog::OnOK();
}

void CConfigDialog::SaveZoomSettings()
{
/*
	CString szRememberZoom;
	
	if (((CButton*)GetDlgItem(IDC_REMEMBER_ZOOM))->GetCheck()) 
		szRememberZoom = "1";
	else
		szRememberZoom = "0";	
		
	CString strZoomLevel = L"";
	
	GetDlgItemText(IDC_ZOOM, strZoomLevel);	
	
	HKEY zoomLevel;
	HKEY zoomRemember;
	if (RegCreateKeyEx (HKEY_LOCAL_MACHINE, 
		L"MobileXPdf\\Settings\\zoomLevel", 0 ,
		NULL,
		REG_OPTION_NON_VOLATILE,
		KEY_SET_VALUE,
		NULL,
		&zoomLevel,
		NULL
		) != ERROR_SUCCESS)
	{
		MessageBox(L"Cannot open zoom level key");
	}
	RegSetValueEx(zoomLevel,0,0,REG_SZ,(BYTE*)strZoomLevel.GetBuffer(0),18);
	RegCloseKey(zoomLevel);

	if (RegCreateKeyEx (HKEY_LOCAL_MACHINE, 
		L"MobileXPdf\\Settings\\zoomRemember", 0 ,
		NULL,
		REG_OPTION_NON_VOLATILE,
		KEY_SET_VALUE,
		NULL,
		&zoomRemember,
		NULL
		) != ERROR_SUCCESS)
	{
		MessageBox(L"Cannot open last zoom");
	}
	RegSetValueEx(zoomRemember,0,0,REG_SZ,(BYTE*)szRememberZoom.GetBuffer(0),18);
	RegCloseKey(zoomRemember);
*/
}

void CConfigDialog::LoadZoomSettings()
{
/*
	HKEY key;
	//zoom level
	double res = 100.0;
	//zoom remember
	if (RegOpenKeyEx(HKEY_LOCAL_MACHINE,L"MobileXPdf\\Settings\\zoomLevel",0,KEY_QUERY_VALUE,&key)==ERROR_SUCCESS)
	{
		wchar_t sw_zoomLevel[256];
		DWORD size=512;
		DWORD type=REG_SZ;
		RegQueryValueEx(key,0,0,&type,(BYTE*)sw_zoomLevel,&size);
		RegCloseKey(key);

		

		res  = (sw_zoomLevel[0] - 48) * 100;
		res += (sw_zoomLevel[1] - 48) * 10;
		res += sw_zoomLevel[2] - 48;

		this->zoomLevel = res;

		if (res < -400.5 || res > 400.5 )
			SetDlgItemText(IDC_ZOOM, L"100");	//safety first!	
		else
			SetDlgItemText(IDC_ZOOM, sw_zoomLevel);


	}

	


	//if (RegOpenKeyEx(HKEY_LOCAL_MACHINE,L"MobileXPdf\\Settings\\zoomLevel",0,KEY_QUERY_VALUE,&key)==ERROR_SUCCESS)
	//{
	//	wchar_t swZoomLevel[256];
	//	DWORD size=512;
	//	DWORD type=REG_SZ;
	//	RegQueryValueEx(key,0,0,&type,(BYTE*)swZoomLevel,&size);
	//	RegCloseKey(key);
	//	SetDlgItemText(IDC_ZOOM, (LPCWSTR)swZoomLevel);
	//}
	//else
	//{
	//	zoomLevel = 100;
	//	SetDlgItemText(IDC_ZOOM, (LPCTSTR)zoomLevel);//default 100%
	//}

	//zoom remember - not yet fully implemented
	if (RegOpenKeyEx(HKEY_LOCAL_MACHINE,L"MobileXPdf\\Settings\\zoomRemember",0,KEY_QUERY_VALUE,&key)==ERROR_SUCCESS)
	{
		wchar_t zoomRemember[256];
		DWORD size=512;
		DWORD type=REG_SZ;
		RegQueryValueEx(key,0,0,&type,(BYTE*)zoomRemember,&size);
		RegCloseKey(key);
		
		((CButton*)(GetDlgItem(IDC_REMEMBER_ZOOM)))->SetCheck(atoi((char*)zoomRemember) == 1? 1: 0);
		if (((CButton*)(GetDlgItem(IDC_REMEMBER_ZOOM)))->GetCheck())
			GetDlgItem(IDC_ZOOM)->EnableWindow(FALSE);		
	}	
*/
}


void CConfigDialog::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	OnOK();
}

void CConfigDialog::setupButtons()
{
	m_MapButtonBox.ResetContent();
	m_MapButtonBox.SetItemData(m_MapButtonBox.AddString(L"Up"),VK_UP);
	m_MapButtonBox.SetItemData(m_MapButtonBox.AddString(L"Down"),VK_DOWN);
	m_MapButtonBox.SetItemData(m_MapButtonBox.AddString(L"Left"),VK_LEFT);
	m_MapButtonBox.SetItemData(m_MapButtonBox.AddString(L"Right"),VK_RIGHT);
	m_MapButtonBox.SetItemData(m_MapButtonBox.AddString(L"Center"),VK_RETURN);
	m_MapButtonBox.SetItemData(m_MapButtonBox.AddString(L"Record"),VK_F10);
	for (int i=6; m_ButtonMappings[i].button!=-1; i++)
	{
		CString button;
		button.Format(L"Button #%d",m_ButtonMappings[i].button);
		m_MapButtonBox.SetItemData(m_MapButtonBox.AddString(button),m_ButtonMappings[i].button);
	}

	/*if (m_MapHWButtons){
		m_MapButtonBox.SetItemData(m_MapButtonBox.AddString(L"HW-Button 1"),0xc1);
		m_MapButtonBox.SetItemData(m_MapButtonBox.AddString(L"HW-Button 2"),0xc2);
		m_MapButtonBox.SetItemData(m_MapButtonBox.AddString(L"HW-Button 3"),0xc3);
		m_MapButtonBox.SetItemData(m_MapButtonBox.AddString(L"HW-Button 4"),0xc4);
		m_MapButtonBox.SetItemData(m_MapButtonBox.AddString(L"HW-Button 5"),0xc5);
	}*/
}

void CConfigDialog::OnToggleMapHWButtons()
{
	UpdateData();
	setupButtons();
}

void CConfigDialog::OnBnClickedSelectbutton()
{
	CButtonGrabberDialog bgd;
	bgd.DoModal();
	
	CString str;
	if (bgd.m_key)
	{
		switch (bgd.m_key)
		{
		case VK_UP:
			m_MapButtonBox.SelectString(-1,L"Up");
			OnCbnSelchangeMapbuttons();
			return;
		case VK_DOWN:
			m_MapButtonBox.SelectString(-1,L"Down");
			OnCbnSelchangeMapbuttons();
			return;
		case VK_LEFT:
			m_MapButtonBox.SelectString(-1,L"Left");
			OnCbnSelchangeMapbuttons();
			return;
		case VK_RIGHT:
			m_MapButtonBox.SelectString(-1,L"Right");
			OnCbnSelchangeMapbuttons();
			return;
		case VK_RETURN:
			m_MapButtonBox.SelectString(-1,L"Center");
			OnCbnSelchangeMapbuttons();
			return;
		case VK_F10:
			m_MapButtonBox.SelectString(-1,L"Record");
			OnCbnSelchangeMapbuttons();
			return;
		}
		CString button;
		button.Format(L"Button #%d",bgd.m_key);
		if (m_MapButtonBox.SelectString(-1,button)==CB_ERR)
		{
			int index=m_MapButtonBox.AddString(button);
			m_MapButtonBox.SetItemData(index,bgd.m_key);
			m_MapButtonBox.SetCurSel(index);
			OnCbnSelchangeMapbuttons();
		}
	}
	if (bgd.m_hotkey)
	{
		CString button;
		button.Format(L"Button #%d",bgd.m_hotkey);
		if (m_MapButtonBox.SelectString(-1,button)==CB_ERR)
		{
			int index=m_MapButtonBox.AddString(button);
			m_MapButtonBox.SetItemData(index,bgd.m_hotkey);
			m_MapButtonBox.SetCurSel(index);
			OnCbnSelchangeMapbuttons();
		}
	}
}

void CConfigDialog::OnBnClickedCancel()
{
	// TODO: Add your control notification handler code here
	OnCancel();
}

void CConfigDialog::OnBnClickedRememberZoom()
{
	if (((CButton*)GetDlgItem(IDC_REMEMBER_ZOOM))->GetCheck())		
		((CEdit*)GetDlgItem(IDC_ZOOM))->EnableWindow(FALSE);
	else
		((CEdit*)GetDlgItem(IDC_ZOOM))->EnableWindow(TRUE);
}

void CConfigDialog::OnBnClickedFileassoc()
{
	// TODO: Add your control notification handler code here
}

void CConfigDialog::OnDeltaposSpin(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);
	
	//CString strZoomLvl;
	//GetDlgItemText(IDC_ZOOM, strZoomLvl);

	////if (pNMUpDown )

	//

	//if (atoi(strZoomLvl.GetBuffer(0)) > 100)
	//{
	//	strZoomLvl = CString(atoi(strZoomLvl.GetBuffer(0)) + 25);
	//	SetDlgItemText(IDC_ZOOM, strZoomLvl);
	//}
	//else
	//	SetDlgItemText(IDC_ZOOM, "100");

	//if (atoi(strZoomLvl.GetBuffer(0)) < 500)
	//{
	//	strZoomLvl = CString(atoi(strZoomLvl.GetBuffer(0)) - 25);
	//	SetDlgItemText(IDC_ZOOM, strZoomLvl);
	//}
	//else
	//	SetDlgItemText(IDC_ZOOM, "500");





	*pResult = 0;
}

void CConfigDialog::OnEnChangeZoom()
{
	CString strZoomTxt;
	GetDlgItemText(IDC_ZOOM, strZoomTxt);

	if (strZoomTxt.GetLength() > 3)
	{
		strZoomTxt.Delete(3);
		SetDlgItemText(IDC_ZOOM, strZoomTxt);
	}
	if (_wtoi(strZoomTxt.GetBuffer()) > 500)
	{
		strZoomTxt = "500";
		SetDlgItemText(IDC_ZOOM, strZoomTxt);
	}

	if (_wtoi(strZoomTxt.GetBuffer()) < 100)
	{
		strZoomTxt = "100";
		SetDlgItemText(IDC_ZOOM, strZoomTxt);
	}
}
