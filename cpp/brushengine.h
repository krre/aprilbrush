#ifndef BRUSHENGINE_H
#define BRUSHENGINE_H

#ifndef NOMINMAX
#define NOMINMAX // fixing compile error with MSVC
#endif

#include "painteditem.h"

#ifdef Q_OS_WIN
#include "windows.h"
#include "wintab/wintab.h"
#define PACKETDATA PK_NORMAL_PRESSURE
#define PACKETMODE 0
#include "wintab/pktdef.h"
#endif

#include <QBuffer>

#ifdef Q_OS_WIN
typedef UINT (API *PtrWTInfo)(UINT, UINT, LPVOID);
typedef HCTX (API *PtrWTOpen)(HWND, LPLOGCONTEXT, BOOL);
typedef int (API *PtrWTPacketsGet)(HCTX, int, LPVOID);
typedef int (API *PtrWTPacket)(HCTX, UINT, LPVOID);
typedef int (API *PtrWTQueuePacketsEx)(HCTX, UINT FAR*, UINT FAR*);
#endif

class BrushEngine : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int size READ size WRITE setSize)
    Q_PROPERTY(int spacing READ spacing WRITE setSpacing)
    Q_PROPERTY(int hardness READ hardness WRITE setHardness)
    Q_PROPERTY(QColor color READ color WRITE setColor)
    Q_PROPERTY(int opacity READ opacity WRITE setOpacity)
    Q_PROPERTY(int roundness READ roundness WRITE setRoundness)
    Q_PROPERTY(int angle READ angle WRITE setAngle)
    Q_PROPERTY(bool eraser READ eraser WRITE setEraser)
    Q_PROPERTY(QString layerId READ layerId WRITE setLayerId)
    Q_PROPERTY(ImageProcessor* imageProcessor READ imageProcessor WRITE setImageProcessor)

public:
    BrushEngine();
    ~BrushEngine();
    Q_INVOKABLE void paintDab(qreal xPos, qreal yPos);
    Q_INVOKABLE void setTouch(bool touch);
    Q_INVOKABLE void clear() { pixmap->fill(QColor(0, 0, 0, 0)); emit paintDone(pixmap->rect()); }
    Q_INVOKABLE QPoint startPos() { return minPos; }
    Q_INVOKABLE QByteArray undoArea() { return undoByteArray; }
    Q_INVOKABLE QByteArray redoArea() { return redoByteArray; }
    Q_INVOKABLE QByteArray currentArea() { return compressPixmap(*pixmap); }
    ImageProcessor* imageProcessor() const { return m_imageProcessor; }

    QString layerId() const { return m_layerId; }

public slots:
    void setLayerId(QString arg);
    void setImageProcessor(ImageProcessor* arg) { m_imageProcessor = arg; }

signals:
    void sizeBrushSignal();
    void paintDone(QRect rect);

private:
    inline int size() {return sizeBrush;}
    inline void setSize(int size) { sizeBrush = size; emit sizeBrushSignal(); }
    inline int spacing() { return spacingBrush; }
    inline void setSpacing(int spacing) { spacingBrush = spacing; }
    inline int hardness() { return hardnessBrush; }
    inline void setHardness(int hardness) { hardnessBrush = hardness; }
    inline QColor color() { return colorBrush; }
    inline void setColor(QColor color) { colorBrush = color; }
    inline int opacity() { return opacityBrush; }
    inline void setOpacity(int opacity) { opacityBrush = opacity; }
    inline int roundness() { return roundnessBrush; }
    inline void setRoundness(int roundness) { roundnessBrush = roundness; }
    inline int angle() { return angleBrush; }
    inline void setAngle(int angle) { angleBrush = angle; }
    inline bool eraser() { return eraserBrush; }
    inline void setEraser(bool eraser) { eraserBrush = eraser; }

    #ifdef Q_OS_WIN
    void wintabInit();
    HINSTANCE ghWintab;
    HCTX tabletHandle;
    PtrWTInfo ptrWTInfo;
    PtrWTOpen ptrWTOpen;
    PtrWTPacket ptrWTPacket;
    PtrWTQueuePacketsEx ptrWTQueuePacketsEx;
    #endif

    QByteArray compressPixmap(QPixmap pixmap);

    int sizeBrush;
    int spacingBrush;
    int hardnessBrush;
    int roundnessBrush;
    int angleBrush;
    QColor colorBrush;
    int opacityBrush;
    bool eraserBrush;
    QPixmap *prevPixmap;
    PaintedItem *paintedItem;
    QByteArray undoByteArray;
    QByteArray redoByteArray;

    QPointF nowPos;
    QPointF prevPos;
    QPoint minPos;
    QPoint maxPos;
    bool touchPen;

    //QTime time;
    qreal pressure();
    QString m_layerId;
    QPixmap *pixmap;
    ImageProcessor *m_imageProcessor;
};


#endif // BRUSHENGINE_H
