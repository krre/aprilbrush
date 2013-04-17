#ifndef BRUSHENGINE_H
#define BRUSHENGINE_H

#include "imageprocessor.h"

#ifdef Q_OS_WIN
#include "wacom/wacom_win.h"
#endif

#ifdef Q_OS_UNIX
#include "wacom/wacom_unix.h"
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

    Q_INVOKABLE void paintDab(QPoint nowPoint);
    Q_INVOKABLE void setTouch(QPoint nowPoint);
    Q_INVOKABLE void setUnTouch();
    Q_INVOKABLE void clear() { pixmap->fill(QColor(0, 0, 0, 0)); }
    Q_INVOKABLE QPoint startPos() { return minPoint; }
    Q_INVOKABLE QByteArray undoArea() { return undoByteArray; }
    Q_INVOKABLE QByteArray redoArea() { return redoByteArray; }
    Q_INVOKABLE QByteArray currentArea() { return compressPixmap(*pixmap); }
    ImageProcessor* imageProcessor() const { return m_imageProcessor; }

    QString layerId() const { return m_layerId; }

public slots:
    void setLayerId(QString arg);
    void setImageProcessor(ImageProcessor* arg) { m_imageProcessor = arg; }

private:
    inline int size() {return m_size;}
    inline void setSize(int size) { m_size = size; }
    inline int spacing() { return m_spacing; }
    inline void setSpacing(int spacing) { m_spacing = spacing; }
    inline int hardness() { return m_hardness; }
    inline void setHardness(int hardness) { m_hardness = hardness; }
    inline QColor color() { return m_color; }
    inline void setColor(QColor color) { m_color = color; }
    inline int opacity() { return m_opacity; }
    inline void setOpacity(int opacity) { m_opacity = opacity; }
    inline int roundness() { return m_roundness; }
    inline void setRoundness(int roundness) { m_roundness = roundness; }
    inline int angle() { return m_angle; }
    inline void setAngle(int angle) { m_angle = angle; }
    inline bool eraser() { return m_eraser; }
    inline void setEraser(bool eraser) { m_eraser = eraser; }

    Wacom wacom;
    QByteArray compressPixmap(QPixmap pixmap);

    int m_size;
    int m_spacing;
    int m_hardness;
    int m_roundness;
    int m_angle;
    QColor m_color;
    int m_opacity;
    bool m_eraser;
    QPixmap *prevPixmap;
    QByteArray undoByteArray;
    QByteArray redoByteArray;

    QPoint prevPoint;
    QPoint minPoint;
    QPoint maxPoint;
    QString m_layerId;
    QPixmap *pixmap;
    ImageProcessor *m_imageProcessor;
};


#endif // BRUSHENGINE_H
