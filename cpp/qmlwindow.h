#ifndef QMLWINDOW_H
#define QMLWINDOW_H

#ifndef NOMINMAX
#define NOMINMAX // temporary fixing compile error with MSVC
#endif
#include "windows.h"
#include "wintab/wintab.h"
#define PACKETDATA PK_NORMAL_PRESSURE
#define PACKETMODE 0
#include "wintab/pktdef.h"
#include <QQuickView>
#include "brushengine.h"

typedef UINT (API *PtrWTInfo)(UINT, UINT, LPVOID);
typedef HCTX (API *PtrWTOpen)(HWND, LPLOGCONTEXT, BOOL);
typedef int (API *PtrWTPacketsGet)(HCTX, int, LPVOID);
typedef int (API *PtrWTPacket)(HCTX, UINT, LPVOID);
typedef int (API *PtrWTQueuePacketsEx)(HCTX, UINT FAR*, UINT FAR*);

class QmlWindow : public QQuickView
{
    Q_OBJECT

public:
    QmlWindow();
    ~QmlWindow();
    qreal pressure();

private:
    void wintabInit();
    HINSTANCE ghWintab;
    HCTX tabletHandle;
    PtrWTInfo ptrWTInfo;
    PtrWTOpen ptrWTOpen;
    PtrWTPacket ptrWTPacket;
    PtrWTQueuePacketsEx ptrWTQueuePacketsEx;
    BrushEngine *brushEngine;
};

#endif // QMLWINDOW_H
