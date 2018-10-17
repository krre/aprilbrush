#pragma once
#include <QObject>
#include <QColor>
#include <QPointF>

class QPainter;
class CanvasItem;

class BrushEngine : public QObject {
    Q_OBJECT
    Q_PROPERTY(bool isTouch READ getIsTouch WRITE setIsTouch NOTIFY isTouchChanged)
    Q_PROPERTY(QColor color READ getColor WRITE setColor NOTIFY colorChanged)
    Q_PROPERTY(int size READ getSize WRITE setSize NOTIFY sizeChanged)
    Q_PROPERTY(int spacing READ getSpacing WRITE setSpacing NOTIFY spacingChanged)
    Q_PROPERTY(int hardness READ getHardness WRITE setHardness NOTIFY hardnessChanged)
    Q_PROPERTY(int opacity READ getOpacity WRITE setOpacity NOTIFY opacityChanged)
    Q_PROPERTY(int flow READ getFlow WRITE setFlow NOTIFY flowChanged)
    Q_PROPERTY(int roundness READ getRoundness WRITE setRoundness NOTIFY roundnessChanged)
    Q_PROPERTY(int angle READ getAngle WRITE setAngle NOTIFY angleChanged)
    Q_PROPERTY(int jitter READ getJitter WRITE setJitter NOTIFY jitterChanged)
    Q_PROPERTY(int eraser READ getEraser WRITE setEraser NOTIFY eraserChanged)

public:
    Q_INVOKABLE void paint(const QPointF& point, float pressure = 1.0);
    Q_INVOKABLE void setCanvasItem(CanvasItem* canvasItem);
    Q_INVOKABLE void setCanvasBuffer(CanvasItem* canvasBuffer);
    Q_INVOKABLE QByteArray getUndoImage() { return undoImage; }
    Q_INVOKABLE QByteArray getRedoImage() { return redoImage; }
    Q_INVOKABLE QPointF startPos() { return topleft; }

    QColor getColor() const { return color; }
    void setColor(const QColor& color);
    int getSize() const { return size; }
    void setSize(int size);
    int getHardness() const { return hardness; }
    void setHardness(int hardness);
    int getOpacity() const { return opacity; }
    void setOpacity(int opacity);
    int getFlow() const { return flow; }
    void setFlow(int flow);
    int getRoundness() const { return roundness; }
    void setRoundness(int roundness);
    int getAngle() const { return angle; }
    void setAngle(int angle);
    int getSpacing() const { return spacing; }
    void setSpacing(int spacing);
    int getJitter() const { return jitter; }
    void setJitter(int jitter);
    int getEraser() const { return eraser; }
    void setEraser(int eraser);

    bool getIsTouch() const { return isTouch; }
    void setIsTouch(bool isTouch);

signals:
    void colorChanged(QColor color);
    void sizeChanged(int size);
    void hardnessChanged(int hardness);
    void opacityChanged(int opacity);
    void flowChanged(int flow);
    void roundnessChanged(int roundness);
    void angleChanged(int angle);
    void spacingChanged(int spacing);
    void jitterChanged(int jitter);
    void eraserChanged(int eraser);

    void isTouchChanged(bool isTouch);

private:
    void paintDab(const QPointF& point, QPainter& painter);

    QColor color = QColor(Qt::black);
    int size = 30;
    int hardness = 80;
    int opacity = 80;
    int flow = 100;
    int roundness = 100;
    int angle = 0;
    int spacing = 100;
    int jitter = 0;
    int eraser = 0;

    bool isTouch = false;
    CanvasItem* canvasItem;
    CanvasItem* canvasBuffer;

    QPointF startPoint;
    QPointF lastPoint;
    QPoint topleft;
    QPoint bottomright;
    QByteArray undoImage;
    QByteArray redoImage;
};
