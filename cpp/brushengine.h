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
#include "paintspace.h"

typedef UINT (API *PtrWTInfo)(UINT, UINT, LPVOID);
typedef HCTX (API *PtrWTOpen)(HWND, LPLOGCONTEXT, BOOL);
typedef int (API *PtrWTPacketsGet)(HCTX, int, LPVOID);
typedef int (API *PtrWTPacket)(HCTX, UINT, LPVOID);
typedef int (API *PtrWTQueuePacketsEx)(HCTX, UINT FAR*, UINT FAR*);

class BrushEngine : public QObject
{
    Q_OBJECT
    Q_PROPERTY(PaintSpace* source READ source WRITE setSource)
    Q_PROPERTY(int size READ size WRITE setSize)
    Q_PROPERTY(int spacing READ spacing WRITE setSpacing)
    Q_PROPERTY(int hardness READ hardness WRITE setHardness)
    Q_PROPERTY(QColor color READ color WRITE setColor)
    Q_PROPERTY(int opacity READ opacity WRITE setOpacity)
    Q_PROPERTY(int roundness READ roundness WRITE setRoundness)
    Q_PROPERTY(int angle READ angle WRITE setAngle)

public:
    BrushEngine();
    ~BrushEngine();
    Q_INVOKABLE void paintDab(qreal xPos, qreal yPos);
    Q_INVOKABLE void setTouch(bool touch) { touchPen = touch; }
    Q_INVOKABLE void clear() { pixmap->fill(QColor(0, 0, 0, 0)); paintSpace->update(); }
    Q_INVOKABLE void setSource (PaintSpace *source) { paintSpace = source; pixmap = &paintSpace->pixmap; /*qDebug() << paintSpace*/; }
    //inline void setEraser(bool eraserOut) { eraser = eraserOut; }
    //inline bool touch() { return touchPen; }

signals:
    void sizeBrushSignal();
    void paintDone();

private:
    inline PaintSpace* source() { return paintSpace; }
    inline int size() {return sizeBrush;}
    inline void setSize(int size) {sizeBrush = size; emit sizeBrushSignal();}
    inline int spacing() {return spacingBrush;}
    inline void setSpacing(int spacing) {spacingBrush = spacing;}
    inline int hardness() {return hardnessBrush;}
    inline void setHardness(int hardness) {hardnessBrush = hardness;}
    inline QColor color() {return colorBrush;}
    inline void setColor(QColor color) {colorBrush = color;}
    inline int opacity() {return opacityBrush;}
    inline void setOpacity(int opacity) {opacityBrush = opacity;}

    inline int roundness() {return roundnessBrush;}
    inline void setRoundness(int roundness) {roundnessBrush = roundness;}

    inline int angle() {return angleBrush;}
    inline void setAngle(int angle) {angleBrush = angle;}

    void wintabInit();
    HINSTANCE ghWintab;
    HCTX tabletHandle;
    PtrWTInfo ptrWTInfo;
    PtrWTOpen ptrWTOpen;
    PtrWTPacket ptrWTPacket;
    PtrWTQueuePacketsEx ptrWTQueuePacketsEx;

    int sizeBrush;
    int spacingBrush;
    int hardnessBrush;
    int roundnessBrush;
    int angleBrush;
    QColor colorBrush;
    int opacityBrush;
    bool eraser;
    QPixmap *pixmap;
    PaintSpace *paintSpace;

    QPointF nowPos;
    QPointF prevPos;
    bool touchPen;

    QTime time;
    qreal pressure();
};

#endif // BRUSHENGINE_H
