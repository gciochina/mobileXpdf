
#include "SIPanel.h"

#if USE_SIP


BOOL    SIPanel::mFoundSip = FALSE;
CLSID   SIPanel::mFoundSipCLSID;
TCHAR  *SIPanel::mSipName;

int SIPanel::sipEnumIMFunc( IMENUMINFO* pIMInfo )
{
    if ( _tcscmp( pIMInfo->szName, mSipName ) == 0 )
    {
        mFoundSipCLSID = pIMInfo->clsid;
        mFoundSip = TRUE;

        return 0; 
    }
    else
        return 1; 
}

BOOL SIPanel::getSipCLSID ( TCHAR* sipName, CLSID &outClsid )
{
    if ( mSipName != NULL )
    {
        delete[] mSipName;
    }

    mSipName = new TCHAR[ _tcslen( sipName )+1 ];
    _tcscpy( mSipName, sipName );

    mFoundSip = FALSE;
    SipEnumIM( sipEnumIMFunc );

    if ( mFoundSip )
        outClsid = mFoundSipCLSID;        

    return mFoundSip;
}

SIPanel::SIPanel() 
{}

SIPanel::~SIPanel()
{
    if ( mSipName != NULL )
    {
        delete[] mSipName;
        mSipName = NULL;
    }
}

void SIPanel::show()
{
    SipShowIM( SIPF_ON );
}

void SIPanel::hide()
{
    SipShowIM( SIPF_OFF );
}

BOOL SIPanel::set( TCHAR* sipName )
{
    BOOL result = FALSE;

    if ( sipName != NULL ) 
    {
        if ( mSipName == NULL || _tcscmp( mSipName, sipName ) != 0 )
        {
            CLSID outClsid;
            if ( getSipCLSID ( sipName, outClsid ) )
            {
                mSipCLSID = outClsid;
                result = SipSetCurrentIM( &mSipCLSID );
            }
        }
    }

    return result;
}

SIPanel& SIPanel::getInstance()
{
    static SIPanel inputPanel;

    return inputPanel;
}

#endif
