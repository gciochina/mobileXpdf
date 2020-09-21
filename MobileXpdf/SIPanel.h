#ifndef _SIPANEL_H_
#define _SIPANEL_H_

#include "MxpdfConfig.h"

#if USE_SIP

#include "stdafx.h"
#include "Sipapi.h"

class SIPanel 
{
private :
    CLSID   mSipCLSID;
    static BOOL    mFoundSip;
    static CLSID   mFoundSipCLSID;
    static TCHAR  *mSipName;

private :

    static int sipEnumIMFunc( IMENUMINFO* pIMInfo );
    BOOL getSipCLSID ( TCHAR* sipName, CLSID &outClsid );

    SIPanel(); 
    ~SIPanel();
    SIPanel( SIPanel const& );        
    void operator= (SIPanel const& ); 

public :

    void show();
    void hide();
    BOOL set( TCHAR* sipName );
    static SIPanel& getInstance();
};

#endif


#endif