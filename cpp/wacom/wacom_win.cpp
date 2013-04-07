#include "wacom_win.h"

#include <QDebug>

Wacom::Wacom()
{
    wintabInit();
}

Wacom::~Wacom()
{
    if (ghWintab)
    {
        ptrWTClose(tabletHandle);
        FreeLibrary(ghWintab);
    }
}

void Wacom::wintabInit()
{
    ghWintab = LoadLibraryA("Wintab32.dll");
    //qDebug() << "LoadLibrary: " << ghWintab;
    if (!ghWintab)
        return;

    ptrWTInfo = (PtrWTInfo)GetProcAddress(ghWintab, "WTInfoW");
    ptrWTOpen = (PtrWTOpen)GetProcAddress(ghWintab, "WTOpenW");
    ptrWTClose = (PtrWTClose)GetProcAddress(ghWintab, "WTClose");
    ptrWTPacket = (PtrWTPacket)GetProcAddress(ghWintab, "WTPacket");
    ptrWTPacketsGet = (PtrWTPacketsGet)GetProcAddress(ghWintab, "WTPacketsGet");
    ptrWTQueuePacketsEx = (PtrWTQueuePacketsEx)GetProcAddress(ghWintab, "WTQueuePacketsEx");

    // Check device name
    char deviceName[50] = {0};
    ptrWTInfo(WTI_DEVICES, DVC_NAME, deviceName);
    //qDebug() << (const char*)&deviceName;

    // Check pressure range
    AXIS range;
    ptrWTInfo(WTI_DEVICES, DVC_NPRESSURE, &range);
    //qDebug() << range.axMax;
    pressureRange = range.axMax;

    // Default context
    LOGCONTEXT tabletContext;
    ptrWTInfo(WTI_DEFCONTEXT, 0, &tabletContext);
    //qDebug() << "Context: " << wacomContext.lcName;

    // Modify the region
    tabletContext.lcPktData = PACKETDATA;
    tabletContext.lcPktMode = PACKETMODE;
    tabletContext.lcMoveMask = PACKETDATA;
    tabletContext.lcOptions |= CXO_SYSTEM; // enable tablet cursor move

    HWND windowHandle = GetDesktopWindow();
    //qDebug() << "Window handle: " << windowHandle;

    tabletHandle = ptrWTOpen(windowHandle, &tabletContext, true);
    //qDebug() << "Tablet handle: " << tabletHandle;
}

qreal Wacom::pressure()
{
    qreal pressure = 1;

    if (ghWintab)
    {
        PACKET packetBuf[128];
        int packetsNum = ptrWTPacketsGet(tabletHandle, 128, packetBuf);
        //qDebug() << packetsNum;
        // If number packets in queue > 0, get first packet, else last from previos queue
        if (packetsNum)
        {
            packet = packetBuf[0];
            pressure = (qreal)packet.pkNormalPressure / pressureRange;
            // Save last packet for next event, if the queut to be empty
            packet = packetBuf[packetsNum > 1 ? packetsNum - 1 : 0];
        }
        else
            pressure = (qreal)packet.pkNormalPressure / pressureRange;
    }
    //qDebug() << "pressure " << pressure;
    return pressure;
}
