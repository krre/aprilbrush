/* AprilBrush - Digital Painting Software
 * Copyright (C) 2012-2013 Vladimir Zarypov <krre@mail.ru>
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation;
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 */

#include "wacom_unix.h"
#include <QDebug>
#include "X11/Xlib.h"
#include "X11/extensions/XInput.h"

Display *x11Display;

Wacom::Wacom()
{
    wacomInit();
}

Wacom::~Wacom()
{
    XCloseDisplay(x11Display);
}

void Wacom::wacomInit()
{
    if ((x11Display = XOpenDisplay(NULL)) == NULL)
    {
        qDebug() << "Can not connect to the X server";
        return;
    }

    int numDevices;
    XDeviceInfo *deviceInfo;
    deviceInfo = XListInputDevices(x11Display, &numDevices);

    XAnyClassPtr any;
    XValuatorInfoPtr v;
    XAxisInfoPtr a;
    XEventClass eventList[numDevices];
    XEventClass anyEventClass[1];
    wacomId = 0;

    for (int i = 0; i < numDevices; i++)
    {
        QString nameDevice = deviceInfo[i].name;
        if (nameDevice.contains("stylus"))
        {
            wacomId = deviceInfo[i].id;
            any = (XAnyClassPtr)deviceInfo[i].inputclassinfo;
            for (int j = 0; j < deviceInfo[i].num_classes; j++)
            {
                if (any->c_class == ValuatorClass)
                {
                    v = (XValuatorInfoPtr)any;
                    a = (XAxisInfoPtr)((char *)v + sizeof(XValuatorInfo));
                    pressureRange = a[2].max_value - a[2].min_value;
                }
                any = (XAnyClassPtr)((char*)any + any->length);
            }
        }

        // Set the allowed event classes
        XDevice *device;
        device = XOpenDevice(x11Display, deviceInfo[i].id);
        if (device)
        {
            int motionType;
            DeviceMotionNotify(device, motionType, eventList[i]);
            XCloseDevice(x11Display, device);
            anyEventClass[0] = eventList[i];
        }
        else
            eventList[i] = 0;
    }

    // Set an event class of not existing device to event class of any existing device
    for (int i = 0; i < numDevices; i++)
        if (!eventList[i])
            eventList[i] = anyEventClass[0];

    // Set root window by the source events
    unsigned long screen;
    screen = DefaultScreen(x11Display);
    Window rootWindow = RootWindow(x11Display, screen);
    XSelectExtensionEvent(x11Display, rootWindow, eventList, numDevices);
}

qreal Wacom::pressure()
{
    qreal pressure = 1.0;

    if (!x11Display)
        return pressure;

    XEvent event;
    XSync(x11Display, true);
    XNextEvent(x11Display, &event);
    XDeviceMotionEvent *motion = reinterpret_cast<XDeviceMotionEvent *>(&event);

    if (motion->deviceid == wacomId)
        pressure = (qreal)motion->axis_data[2] / pressureRange;

    return pressure;
}
