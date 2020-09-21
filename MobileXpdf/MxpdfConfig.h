#ifndef _MXPDF_CONFIG_H
    #define _MXPDF_CONFIG_H


#define USE_SIP          1
// use name of SIP method you'd like to use
#define USE_SIP_NAME     _T("Horizon Keyboard") 

// use custom key codes
#define USE_CUSTOM_KEY_CODES

// define user events
#define WM_USER_REFRESHTOOLBAR	(WM_APP + 1)
#define WM_USER_GOTOPAGE        (WM_APP + 2)

#define MOUSE_PLUG_HANDLING

#ifdef MOUSE_PLUG_HANDLING
#define MOUSE_PLUG_DLL_PATH     L"\\Applications\\StartingShellApp\\DevMan.dll"
#define WM_MOUSEPLUGGED         (WM_APP + 100)
#define WM_MOUSEUNPLUGGED       (WM_APP + 101)
#endif

#endif