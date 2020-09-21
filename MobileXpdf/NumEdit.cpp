// NumEdit.cpp : implementation file
//

#include "stdafx.h"
#include "MobileXpdf.h"
#include "NumEdit.h"
#include "SIPanel.h"


// CNumEdit

IMPLEMENT_DYNAMIC(CNumEdit, CEdit)

CNumEdit::CNumEdit()
{

}

CNumEdit::~CNumEdit()
{
}

void CNumEdit::SetMinMax( int minVal, int maxVal )
{
    mMinVal = minVal;
    mMaxVal = maxVal;
}


BEGIN_MESSAGE_MAP(CNumEdit, CEdit)
    ON_WM_CHAR()
    ON_WM_KILLFOCUS()
    ON_WM_SETFOCUS()
    ON_CONTROL_REFLECT(EN_UPDATE, &CNumEdit::OnEnUpdate)
    ON_CONTROL_REFLECT(EN_CHANGE, &CNumEdit::OnEnChange)
//    ON_WM_LBUTTONUP()
//    ON_WM_LBUTTONDOWN()
ON_WM_SYSKEYDOWN()
END_MESSAGE_MAP()



// CNumEdit message handlers



void CNumEdit::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags)
{
    if ( (nChar == VK_BACK) || ((nChar >= '0' && nChar <= '9') /* && nFlags*/) )
    {
        TCHAR buf[10];
        GetWindowText( buf, 9 );
        if( !(_tcslen(buf) == 0 && nChar == '0') )
            CEdit::OnChar(nChar, nRepCnt, nFlags);
    }
}

void CNumEdit::OnKillFocus(CWnd* pNewWnd)
{
    if ( mRevertOnFocusLost )
    {
        SetWindowText( mRevertBuffer );
        //UpdateData();
    }

    CEdit::OnKillFocus(pNewWnd);

#if USE_SIP
    SIPanel::getInstance().hide();
#endif
}

void CNumEdit::OnSetFocus(CWnd* pOldWnd)
{
    SetRevertOnFocusLost( true );
    GetWindowText( mRevertBuffer );
	SetWindowText( CString() ); // clear content
    CEdit::OnSetFocus(pOldWnd);

#if USE_SIP
    SIPanel::getInstance().set( USE_SIP_NAME );
    SIPanel::getInstance().show();
#endif
}

void CNumEdit::OnEnUpdate()
{
    CString contentString;
    GetWindowText( contentString );
    int pageNum = _ttoi( contentString );

    if ( pageNum )
    {
        BOOL outOfRange = FALSE;
        int endP=0;

        if ( pageNum < mMinVal ) 
        {
            pageNum = mMinVal;
            outOfRange = TRUE;
        }
        else if ( pageNum > mMaxVal ) 
        {
            pageNum = mMaxVal;
            outOfRange = TRUE;
        }

        if ( outOfRange )
        {
            contentString.Format( _T("%d"), pageNum );
            SetWindowText( contentString );
            endP = contentString.GetLength();
            SetSel( endP, endP );
            UpdateData( FALSE );
        }
    }
}

void CNumEdit::OnEnChange()
{
    // TODO:  If this is a RICHEDIT control, the control will not
    // send this notification unless you override the CEdit::OnInitDialog()
    // function and call CRichEditCtrl().SetEventMask()
    // with the ENM_CHANGE flag ORed into the mask.

    // TODO:  Add your control notification handler code here

}
//void CNumEdit::OnLButtonUp(UINT nFlags, CPoint point)
//{
//    // TODO: Add your message handler code here and/or call default
//
//    CEdit::OnLButtonUp(nFlags, point);
//}

//void CNumEdit::OnLButtonDown(UINT nFlags, CPoint point)
//{
//    // TODO: Add your message handler code here and/or call default
//    if ( GetParent()->GetActiveWindow() != GetParent() )
//    {
//        GetParent()->SetActiveWindow();
//        this->EnableWindow();
//        this->SetFocus();
//    }
//    
//     CEdit::OnLButtonDown(nFlags, point);
//}

void CNumEdit::OnSysKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
    // TODO: Add your message handler code here and/or call default

    CEdit::OnSysKeyDown(nChar, nRepCnt, nFlags);
}


void CNumEdit::SetRevertOnFocusLost( BOOL onOff )
{
    mRevertOnFocusLost = onOff;
}