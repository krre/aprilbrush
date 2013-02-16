#ifndef BRUSHENGINE_H
#define BRUSHENGINE_H

#ifndef NOMINMAX
#define NOMINMAX // temporary fixing compile error with MSVC
#endif
#include "windows.h"
#include "wintab/wintab.h"
#define PACKETDATA PK_NORMAL_PRESSURE
#define PACKETMODE 0
#include "wintab/pktdef.h"
#include <QtGui>

typedef UINT (API *PtrWTInfo)(UINT, UINT, LPVOID);
typedef HCTX (API *PtrWTOpen)(HWND, LPLOGCONTEXT, BOOL);
typedef int (API *PtrWTPacketsGet)(HCTX, int, LPVOID);
typedef int (API *PtrWTPacket)(HCTX, UINT, LPVOID);
typedef int (API *PtrWTQueuePacketsEx)(HCTX, UINT FAR*, UINT FAR*);

class BrushEngine : public QObject
{
    Q_OBJECT
    //Q_INVOKABLE void paintDab(qreal xPos, qreal yPos, qreal pressure);

public:
    BrushEngine();
    ~BrushEngine();
    Q_INVOKABLE void paintDab(qreal xPos, qreal yPos);
    inline int diameterBrush() {return sizeBrush;}
    inline void setColor(int r, int g, int b) {rColor = r; gColor = g, bColor = b;}
    inline void setColor(int r, int g, int b, int a) {rColor = r; gColor = g, bColor = b; aColor = a;}
    inline void setEraser(bool eraserOut) {eraser = eraserOut;}
    inline bool touch() {return touchPen;}
    Q_INVOKABLE void setTouch(bool touch) {touchPen = touch;}

signals:
    void sizeBrushSignal();

public slots:
    inline void setSizeBrush(int size) {sizeBrush = size; emit sizeBrushSignal();}
    inline void setAlpha(int alpha) {aColor = int(alpha * 255 / 100);}
    inline void setSpacingBrush(int spacing) {spacingBrush = spacing;}
    inline void setHardnessBrush(int hardness) {hardnessBrush = hardness;}

private:
    void wintabInit();
    HINSTANCE ghWintab;
    HCTX tabletHandle;
    PtrWTInfo ptrWTInfo;
    PtrWTOpen ptrWTOpen;
    PtrWTPacket ptrWTPacket;
    PtrWTQueuePacketsEx ptrWTQueuePacketsEx;

    QColor colorBrush;
    int sizeBrush;
    int spacingBrush;
    int hardnessBrush;
    bool eraser;

    QPointF nowPos;
    QPointF prevPos;
    bool touchPen;

    int rColor;
    int gColor;
    int bColor;
    int aColor;

    QTime time;
    qreal pressure();
};

#endif // BRUSHENGINE_H
