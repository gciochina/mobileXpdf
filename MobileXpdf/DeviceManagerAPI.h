// The following ifdef block is the standard way of creating macros which make exporting 
// from a DLL simpler. All files within this DLL are compiled with the MPDETECT_EXPORTS
// symbol defined on the command line. this symbol should not be defined on any project
// that uses this DLL. This way any other project whose source files include this file see 
// MPDETECT_API functions as being imported from a DLL, whereas this DLL sees symbols
// defined with this macro as being exported.
#ifdef MPDETECT_EXPORTS
#define MPDETECT_API __declspec(dllexport)
#else
#define MPDETECT_API __declspec(dllimport)
#endif

typedef LONG DMHandle; 

    /*!
     * \brief Mouse plug\unplug callback type
     * \param [in] true: if mouse is plugged, false: in mouse in unplugged 
     */
typedef void (CALLBACK * DMMouseNotificationCallback)(bool);

extern "C" 
{
    
    /*!
     * \brief Create a DeviceManager Object 
     * \return An Handle to the object to use in subsequent calls 
     */
    MPDETECT_API DMHandle DMCreate(void);

    /*!
     * \brief Add a notification callback. This function should be called before calling the DMStart method in order to get the first notification 
     *        dispatched after start.
     * \param [in] Handle to a valid DeviceManager object
     * \param [in] pointer to the callback function
     */
    MPDETECT_API void DMAddNotification(DMHandle handle, DMMouseNotificationCallback callback);

    /*!
     *\brief Starts the notification. It calls the callback to notify if a mouse device is plugged
     *\param [in] Handle to a valid DeviceManager object
     */
    MPDETECT_API bool DMStart(DMHandle handle);

    /*!
    *\brief Stops notifications and releases the resources.
    *\param [in] Handle to a valid DeviceManager object
    */
    MPDETECT_API void DMStop(DMHandle handle);
}

