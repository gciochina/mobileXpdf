#include "MxpdfConfig.h"
#include <windows.h>
#include "MouseDetection.h"


#ifdef _WIN32_WCE

#ifdef MOUSE_PLUG_HANDLING


void CALLBACK MousePluggedHandler(bool plugged)
{
	if (plugged)
		PostMessage(HWND_BROADCAST, WM_MOUSEPLUGGED,0,0);
	else
		PostMessage(HWND_BROADCAST, WM_MOUSEUNPLUGGED,0,0);
}

void cMouseDetection::Init()
{
	HMODULE hm = ::LoadLibrary(MOUSE_PLUG_DLL_PATH);
    
    if (hm)
    {
        create = (Create) GetProcAddress(hm, L"DMCreate");
        start = (Start) GetProcAddress(hm, L"DMStart");
        stop = (Stop) GetProcAddress(hm, L"DMStop");
        addNotification = (AddNotification) GetProcAddress(hm, L"DMAddNotification");

	    if ( create && addNotification && start )
	    {
		    hndle = create();
		    addNotification(hndle, MousePluggedHandler);
    	
		    dmStarted = start(hndle);
	    }
    }
}

void cMouseDetection::Finalize() 
{
	if ( dmStarted )
        stop(hndle);
}

cMouseDetection& cMouseDetection::GetInstance()
{
	static cMouseDetection instance;
	return instance;
}

#endif

#endif /* _WIN32_WCE */