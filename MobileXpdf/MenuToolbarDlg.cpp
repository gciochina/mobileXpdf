// MenuToolbar.cpp : implementation file
//

#include "stdafx.h"
#include "MxpdfConfig.h"
#include "MobileXpdf.h"
#include "MenuToolbarDlg.h"

// CMenuToolbarDlg dialog

IMPLEMENT_DYNAMIC(CMenuToolbarDlg, CDialog)

CMenuToolbarDlg::CMenuToolbarDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CMenuToolbarDlg::IDD, pParent), mDocCurrentPage( 0 ), mDocNumOfPages( 0 )
{
	// Resource handle to bitmap.
	HRSRC hRes;    
	// Global handles to bitmap resource.
	HGLOBAL hData;
	void* hLockedData;

	// Find the resource handle.
	hRes = ::FindResource(AfxGetResourceHandle(),
		MAKEINTRESOURCE(IDB_BITMAP_LABEL_FILENAME), RT_BITMAP);

	if (hRes != NULL)
	{
	   // Load and lock.
	   if (((hData = ::LoadResource(AfxGetResourceHandle(), hRes)) != NULL)
		   && ((hLockedData = ::LockResource(hData)) != NULL))
	   {
		  // Initialize the brush.
		  mBrushLabelFilename.CreateDIBPatternBrush((const void*)hLockedData,
			 DIB_RGB_COLORS);

		  // Free the resource.
		  ::FreeResource(hLockedData);
	   }
	}

	// Find the resource handle.
	hRes = ::FindResource(AfxGetResourceHandle(),
		MAKEINTRESOURCE(IDB_BITMAP_LABEL_PAGECOUNT), RT_BITMAP);

	if (hRes != NULL)
	{
	   // Load and lock.
	   if (((hData = ::LoadResource(AfxGetResourceHandle(), hRes)) != NULL)
		   && ((hLockedData = ::LockResource(hData)) != NULL))
	   {
		  // Initialize the brush.
		  mBrushLabelPageCount.CreateDIBPatternBrush((const void*)hLockedData,
			 DIB_RGB_COLORS);

		  // Free the resource.
		  ::FreeResource(hLockedData);
	   }
	}

	hRes = ::FindResource(AfxGetResourceHandle(),
		MAKEINTRESOURCE(IDB_BITMAP_EDIT), RT_BITMAP);

	if (hRes != NULL)
	{
	   // Load and lock.
	   if (((hData = ::LoadResource(AfxGetResourceHandle(), hRes)) != NULL)
		   && ((hLockedData = ::LockResource(hData)) != NULL))
	   {
		  // Initialize the brush.
		  mBrushEdit.CreateDIBPatternBrush((const void*)hLockedData,
			 DIB_RGB_COLORS);

		  // Free the resource.
		  ::FreeResource(hLockedData);
	   }
	}
}

CMenuToolbarDlg::~CMenuToolbarDlg()
{
	mAboutDlg.DestroyWindow();
}

void CMenuToolbarDlg::SetPageNum( int currentPage, int numofPages )
{
    mDocCurrentPage = currentPage;
    mDocNumOfPages = numofPages;
    mEditPageNumber.SetMinMax( 1, mDocNumOfPages );

    CString pageString;
    pageString.Format( _T("%d"), mDocCurrentPage );
    mEditPageNumber.SetWindowText( pageString );
}

int CMenuToolbarDlg::Create( UINT nIDTemplate, CWnd *pParentWnd )
{
	/*LOGFONT logFont;
	memset(&logFont, 0, sizeof(logFont));
	logFont.lfHeight = 30;                // character height in pixels
	logFont.lfWidth = 12;                 // character width in pixels
	logFont.lfEscapement = 0;             // orientation of next character
	logFont.lfOrientation = 0;            // orientation of first character
	logFont.lfWeight = FW_NORMAL;           // normal thickness
	logFont.lfItalic = FALSE;             // not italic characters
	logFont.lfUnderline = FALSE;          // not underlined characters
	logFont.lfStrikeOut = FALSE;          // not strikeout characters
	logFont.lfCharSet = ANSI_CHARSET;     // OEM character set
	logFont.lfOutPrecision = 0;           // default output precision
	logFont.lfClipPrecision = 0;          // default clipping precision
	logFont.lfQuality = DEFAULT_QUALITY;  // default scaling quality
	logFont.lfPitchAndFamily = FF_SCRIPT; // default pitch, script font family
	wsprintf(logFont.lfFaceName, _T("MS Shell Dlg"));
	mFont.CreateFontIndirect(&logFont);*/
	// mFont has to be set here

	int retVal = CDialog::Create( nIDTemplate, pParentWnd );
	return retVal;
}

void CMenuToolbarDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//DDX_Control(pDX, IDC_CLOSE, mButtonClose);
	//DDX_Control(pDX, IDC_PREV, mButtonPrev);
	//DDX_Control(pDX, IDC_NEXT, mButtonNext);
	//DDX_Control(pDX, IDC_ABOUT, mButtonAbout);
	//DDX_Control(pDX, IDC_LBL_FILENAME, mLabelFilename);
	//DDX_Control(pDX, IDC_LBL_PAGENUMBER, mLabelPageNumber);
	DDX_Control(pDX, IDC_EDIT_PAGENUMBER, mEditPageNumber);
}

BEGIN_MESSAGE_MAP(CMenuToolbarDlg, CDialog)
	ON_WM_CLOSE()
	ON_WM_ERASEBKGND()
	ON_WM_DESTROY()
	ON_WM_ACTIVATE()
	ON_WM_CTLCOLOR()
	ON_BN_CLICKED(IDC_CLOSE, &CMenuToolbarDlg::OnClose)
	ON_BN_CLICKED(IDC_PREV, &CMenuToolbarDlg::OnPrevPage)
	ON_BN_CLICKED(IDC_NEXT, &CMenuToolbarDlg::OnNextPage)
	ON_BN_CLICKED(IDC_ABOUT, &CMenuToolbarDlg::OnBnClickedAbout)
END_MESSAGE_MAP()

BOOL CMenuToolbarDlg::OnInitDialog()
{
	CDialog::OnInitDialog();
	ShowWindow(SW_SHOWNORMAL);

	// Load bitmap from resource, get bitmap size
	mBackground.LoadBitmapW(IDB_BITMAP_SLIDEBAR);
	BITMAP bm; // create bitmap handle to get dimensions
	mBackground.GetBitmap(&bm); // load bitmap into handle
	mBitmapSize = CSize(bm.bmWidth, bm.bmHeight); // get bitmap sizes

	mButtonClose.AutoLoad( IDC_CLOSE, this );
	mButtonPrev.AutoLoad( IDC_PREV, this );
	mButtonNext.AutoLoad( IDC_NEXT, this );
	mButtonAbout.AutoLoad( IDC_ABOUT, this );
	mLabelFilename = (CStatic*)(GetDlgItem( IDC_LBL_FILENAME ));
	mLabelPageNumber = (CStatic*)(GetDlgItem( IDC_LBL_PAGENUMBER ));

	/*RECT rectDesktop;
	CRect rectButton;
	int buttonMargin = 4;
	GetDesktopWindow()->GetWindowRect(&rectDesktop);
	mButtonClose.GetWindowRect(&rectButton);
	int xoffset = rectDesktop.right / 2 - static_cast<int>( rectButton.Width() * 1.5 ) - buttonMargin;
	mButtonClose.SetWindowPos( NULL, rectDesktop.right - rectButton.Width() - buttonMargin, buttonMargin, rectButton.Width(), rectButton.Height(), SWP_NOZORDER );
	mButtonPrev.SetWindowPos( NULL, xoffset, buttonMargin, rectButton.Width(), rectButton.Height(), SWP_NOZORDER );
	mButtonNext.SetWindowPos( NULL, xoffset + 2*buttonMargin + 2*rectButton.Width(), buttonMargin, rectButton.Width(), rectButton.Height(), SWP_NOZORDER );*/
	
	HDC screen = ::GetDC( NULL );
	int res = ::GetDeviceCaps( screen, LOGPIXELSX );
	DWORD DlgUnits = GetDialogBaseUnits();
	CDC *pdcFilename = mLabelFilename->GetDC();
	
	CRect lblRect;
	GetDlgItem( IDC_LBL_FILENAME )->GetWindowRect( &lblRect );

	TCHAR   szDrive[_MAX_DRIVE] = { 0 };
	TCHAR   szDir[_MAX_DIR]     = { 0 };
	TCHAR   szFname[_MAX_FNAME] = { 0 };
	TCHAR   szExt[_MAX_EXT]     = { 0 };
	TCHAR   szFnameExt[MAX_PATH]= { 0 };
	TCHAR	delimiter = _T('.');
	size_t  currentLength;
	CSize	strSize;
	int		strLength; 

	CString cmdLine = AfxGetApp()->m_lpCmdLine;
	if ( !cmdLine.IsEmpty() )
	{
		cmdLine.Remove('"');
		DWORD dwReturnCode = _tsplitpath_s( cmdLine, szDrive, _MAX_DRIVE, szDir, _MAX_DIR, szFname, _MAX_FNAME, szExt, _MAX_EXT );
		if ( dwReturnCode == 0 )
		{
			currentLength = _tcslen( szFname ) + _tcslen( szExt ) + sizeof( TCHAR );
			if( currentLength <= _MAX_DIR )
			{
				_stprintf( szFnameExt, _T("%s%s"), szFname, szExt );
				currentLength = _tcslen( szFnameExt ); // get file name and extension only

				strSize = pdcFilename->GetTextExtent(szFnameExt);
				strLength = (strSize.cx * LOWORD( DlgUnits ))/4 + currentLength;
				
				while ( strLength > 0.9 * lblRect.Width() && currentLength > 3 ) // safety margin
				{
					if ( szFnameExt[currentLength-4] == delimiter )
						currentLength--; // avoid four dots at the end
					_tcsncpy_s(szFnameExt, MAX_PATH, szFnameExt, currentLength-3 );
					for ( int i=0; i<3; i++ )
						_tcsncat_s(szFnameExt, MAX_PATH, &delimiter, 1 );

					strSize = pdcFilename->GetTextExtent(szFnameExt);
					strLength = (strSize.cx * LOWORD( DlgUnits ))/4 + currentLength;

					currentLength--;
				}
				mLabelFilename->SetWindowText( szFnameExt );
			}
		}
	}
	mLabelFilename->ReleaseDC( pdcFilename );

	/*int xMargin = 15;
	int yMargin = 20;
	int width = rectDesktop.right - rectButton.Width() - 2*buttonMargin;
	int height = 40;
	mLabelFilename->SetFont( &mFont, FALSE );
	mLabelFilename->SetWindowPos( NULL, xMargin, yMargin, width, height, SWP_NOZORDER );
	mLabelFilename->ShowWindow( SW_SHOW );*/

	Invalidate(1);
	//End Bitmap Information

	return TRUE;  // return TRUE  unless you set the focus to a control
}

BOOL CMenuToolbarDlg::OnEraseBkgnd(CDC* pDC)
{
	CDC dcMemory;

	dcMemory.CreateCompatibleDC(pDC);
	CBitmap* pOldBitmap = dcMemory.SelectObject(&mBackground);
	CRect rcClient;
	GetClientRect(&rcClient);
	const CSize& sBitmap = mBitmapSize;
	pDC->BitBlt(0,0,sBitmap.cx,sBitmap.cy,&dcMemory,0,0,SRCCOPY);
	dcMemory.SelectObject(pOldBitmap);

	return TRUE;
	//return CDialog::OnEraseBkgnd(pDC); //remove and return TRUE
}

void CMenuToolbarDlg::OnClose()
{
	GetParent()->PostMessage( WM_CLOSE, 0, 0 );
}

void CMenuToolbarDlg::OnActivate(UINT nState, CWnd* pWndOther, BOOL bMinimized)
{
}

void CMenuToolbarDlg::OnPrevPage()
{
	GetParent()->PostMessage( WM_COMMAND, ID_PREV_PAGE );
}

void CMenuToolbarDlg::OnNextPage()
{
	GetParent()->PostMessage( WM_COMMAND, ID_NEXT_PAGE );
}

void CMenuToolbarDlg::OnDestroy()
{
	CDialog::OnDestroy();

	mBackground.DeleteObject(); // delete background bitmap
	mBrushLabelFilename.DeleteObject();
	mBrushLabelPageCount.DeleteObject();
	mBrushEdit.DeleteObject();
}

HBRUSH CMenuToolbarDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	//HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);
	if ( pWnd->GetDlgCtrlID() == IDC_EDIT_PAGENUMBER )
	{
		pDC->SetTextColor(RGB(0, 0, 0));
		pDC->SetBkMode(TRANSPARENT);
		// Return a different brush than default
		return mBrushEdit;
	}
	if ( pWnd->GetDlgCtrlID() == IDC_LBL_PAGENUMBER )
	{
		pDC->SetTextColor(RGB(255, 255, 255));
		pDC->SetBkMode(TRANSPARENT);
		// Return a different brush than default
		return mBrushLabelPageCount;
	}
	if( pWnd->GetDlgCtrlID() == IDC_LBL_FILENAME )
	{
		pDC->SetTextColor(RGB(255, 255, 255));
		pDC->SetBkMode(TRANSPARENT);
	}
	// Return a different brush than default
	return mBrushLabelFilename;
}

void CMenuToolbarDlg::setCaption(LPWSTR text)
{
	mLabelPageNumber = (CStatic*)(GetDlgItem( IDC_LBL_PAGENUMBER ));
	mLabelPageNumber->SetWindowText( text );
	mEditPageNumber.ShowWindow( SW_SHOWNA );
}

void CMenuToolbarDlg::enableButtonPrev(BOOL state)
{
	CWnd* pWnd = GetDlgItem( IDC_PREV );
	if ( pWnd != NULL )
	{
		pWnd->EnableWindow( state );
	}
}

void CMenuToolbarDlg::enableButtonNext(BOOL state)
{
	CWnd* pWnd = GetDlgItem( IDC_NEXT );
	if ( pWnd != NULL )
	{
		pWnd->EnableWindow( state );
	}
}

BOOL CMenuToolbarDlg::PreTranslateMessage(MSG* pMsg)
{
    if (pMsg->message == WM_KEYDOWN &&
        pMsg->wParam == VK_RETURN &&
        GetFocus() == &mEditPageNumber )
    {
        // handle return pressed in edit control
        CString contentString;
        mEditPageNumber.GetWindowText( contentString );

        int pageNum = _ttoi( contentString );

        if ( pageNum != 0 )
        {
            mEditPageNumber.SetRevertOnFocusLost( false );
        }

        GetParent()->SetFocus();
        UpdateWindow();
        GetParent()->PostMessage( WM_PAINT );

        if ( pageNum != 0 )
        {
            GetParent()->PostMessage( WM_USER_GOTOPAGE, pageNum, 0 );
        }

        return TRUE; // this doesn't need processing anymore
    }
    else
        return CDialog::PreTranslateMessage(pMsg);
}

void CMenuToolbarDlg::OnBnClickedAbout()
{
	//AfxGetMainWnd()->PostMessage( WM_COMMAND, ID_APP_ABOUT ); // old about page
	mAboutDlg.DoModal();
	GetParent()->SetFocus();
}
