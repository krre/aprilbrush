#include "wacom_unix.h"
#include "xcb/xproto.h"
//#include "xcb/xcbext.h"
//#include "xcb/xcb_atom.h"

#include <QDebug>

Wacom::Wacom()
{
}

Wacom::~Wacom()
{
    xcb_disconnect(xcbConnection);
}

void Wacom::wacomInit()
{
    xcbConnection = xcb_connect(NULL, NULL);
    //qDebug() << "xcbConnection" << xcbConnection;

    // Get id for current (in focus) window
    xcb_get_input_focus_reply_t *focus = xcb_get_input_focus_reply(xcbConnection, xcb_get_input_focus(xcbConnection), NULL);
    xcb_window_t currentWindow = focus->focus;
    free(focus);
    //qDebug() << "focus" << currentWindow;

    uint32_t values[] = { XCB_EVENT_MASK_POINTER_MOTION };
    //uint32_t values[] = { XCB_EVENT_MASK_BUTTON_1_MOTION | XCB_EVENT_MASK_POINTER_MOTION };
    xcb_change_window_attributes(xcbConnection, currentWindow, XCB_CW_EVENT_MASK, values);
}

qreal Wacom::pressure()
{
    /*
    if (!xcbConnection)
        wacomInit();
    qDebug() << "connection" << xcbConnection;

    xcb_generic_event_t *event;
    while (event = xcb_poll_for_event(xcbConnection))
    {
        xcb_motion_notify_event_t *eventValue = (xcb_motion_notify_event_t *)event;
        qDebug() << eventValue->event_x << eventValue->event_y;
        free(eventValue);
    }

    xcb_flush(xcbConnection);*/

   return 1.0;
}

bool XcbEventFilter::nativeEventFilter(const QByteArray &eventType, void *message, long *)
{
    //qDebug() << "eventType" << eventType;
    if (eventType == "xcb_generic_event_t") {
        xcb_generic_event_t* event = static_cast<xcb_generic_event_t *>(message);
        xcb_motion_notify_event_t *eventValue = (xcb_motion_notify_event_t *)event;
        //qDebug() << eventValue->event_x << eventValue->event_y;
    }
    return false;
}
