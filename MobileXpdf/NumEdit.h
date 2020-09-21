#pragma once


// CNumEdit

class CNumEdit : public CEdit
{
	DECLARE_DYNAMIC(CNumEdit)

private:
    int mMinVal;
    int mMaxVal;
    int mVal;
    BOOL mRevertOnFocusLost;
    CString mRevertBuffer;

public:
	CNumEdit();
	virtual ~CNumEdit();
    void SetMinMax( int minVal, int maxVal );
    int GetValue() { return mVal; }
    void SetRevertOnFocusLost( BOOL onOff );

protected:
	DECLARE_MESSAGE_MAP()
public:
    afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
    afx_msg void OnKillFocus(CWnd* pNewWnd);
    afx_msg void OnSetFocus(CWnd* pOldWnd);
    afx_msg void OnEnUpdate();
    afx_msg void OnEnChange();
//    afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
//    afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
    afx_msg void OnSysKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
};


