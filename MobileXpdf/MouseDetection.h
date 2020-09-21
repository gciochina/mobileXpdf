#ifndef __MOUSEDETECTION_H__
#define __MOUSEDETECTION_H__

#ifdef _WIN32_WCE

#include "DeviceManagerAPI.h"

typedef DMHandle (*Create)();
typedef bool (*Start)(DMHandle);
typedef void (*Stop)(DMHandle);
typedef void (*AddNotification)(DMHandle, DMMouseNotificationCallback);

static BOOL dmStarted = FALSE;

/*
 * This class is responsible for mouse detection managing.
 *
 */
class cMouseDetection
{
private:

	Create create;
    Start start;
    Stop stop;
    AddNotification addNotification;

    cMouseDetection(void) : create(0), start(0), stop(0) {};

public:

	void Init();
    void Finalize();
	static cMouseDetection& GetInstance();

private:

	DMHandle hndle;

};

#endif /* _WIN32_WCE */
#endif /* __MOUSEDETECTION_H__ */