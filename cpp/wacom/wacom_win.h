#ifndef WACOM_H
#define WACOM_H

#ifndef NOMINMAX
#define NOMINMAX // fixing compile error with MSVC
#endif

#include "windows.h"
#include "wintab/wintab.h"
#define PACKETDATA PK_NORMAL_PRESSURE
#define PACKETMODE 0
#include "wintab/pktdef.h"

#include <QObject>

typedef UINT (API *PtrWTInfo)(UINT, UINT, LPVOID);
typedef HCTX (API *PtrWTOpen)(HWND, LPLOGCONTEXT, BOOL);
typedef bool (API *PtrWTClose)(HCTX);
typedef int (API *PtrWTPacket)(HCTX, UINT, LPVOID);
typedef int (API *PtrWTPacketsGet)(HCTX, int, LPVOID);
typedef int (API *PtrWTQueuePacketsEx)(HCTX, UINT FAR*, UINT FAR*);

class Wacom  : public QObject
{
public:
    Wacom();
    ~Wacom();
    qreal pressure();

private:

    void wintabInit();
    HINSTANCE ghWintab;
    HCTX tabletHandle;
    PACKET packet;

    PtrWTInfo ptrWTInfo;
    PtrWTOpen ptrWTOpen;
    PtrWTClose ptrWTClose;
    PtrWTPacket ptrWTPacket;
    PtrWTPacketsGet ptrWTPacketsGet;
    PtrWTQueuePacketsEx ptrWTQueuePacketsEx;

    int pressureRange;
};

#endif // WACOM_H
