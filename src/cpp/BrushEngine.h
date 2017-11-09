#pragma once
#include "CanvasItem.h"

class BrushEngine : public QObject {
    Q_OBJECT
    Q_PROPERTY(bool isTouch READ isTouch WRITE setIsTouch NOTIFY isTouchChanged)
    Q_PROPERTY(QColor color READ color WRITE setColor NOTIFY colorChanged)
    Q_PROPERTY(int size READ size WRITE setSize NOTIFY sizeChanged)
    Q_PROPERTY(int spacing READ spacing WRITE setSpacing NOTIFY spacingChanged)
    Q_PROPERTY(int hardness READ hardness WRITE setHardness NOTIFY hardnessChanged)
    Q_PROPERTY(int opacity READ opacity WRITE setOpacity NOTIFY opacityChanged)
    Q_PROPERTY(int flow READ flow WRITE setFlow NOTIFY flowChanged)
    Q_PROPERTY(int roundness READ roundness WRITE setRoundness NOTIFY roundnessChanged)
    Q_PROPERTY(int angle READ angle WRITE setAngle NOTIFY angleChanged)
    Q_PROPERTY(int jitter READ jitter WRITE setJitter NOTIFY jitterChanged)
    Q_PROPERTY(int eraser READ eraser WRITE setEraser NOTIFY eraserChanged)

public:
    Q_INVOKABLE void paint(const QPointF& point, float pressure=1.0);
    Q_INVOKABLE void setCanvasItem(CanvasItem* _canvasItem);
    Q_INVOKABLE void setCanvasBuffer(CanvasItem* canvasBuffer) { this->_canvasBuffer = canvasBuffer; }
    Q_INVOKABLE QByteArray undoImage() { return _undoImage; }
    Q_INVOKABLE QByteArray redoImage() { return _redoImage; }
    Q_INVOKABLE QPointF startPos() { return _topleft; }

    QColor color() const { return _color; }
    void setColor(QColor color);
    int size() const { return _size; }
    void setSize(int size);
    int hardness() const { return _hardness; }
    void setHardness(int hardness);
    int opacity() const { return _opacity; }
    void setOpacity(int opacity);
    int flow() const { return _flow; }
    void setFlow(int flow);
    int roundness() const { return _roundness; }
    void setRoundness(int roundness);
    int angle() const { return _angle; }
    void setAngle(int angle);
    int spacing() const { return _spacing; }
    void setSpacing(int spacing);
    int jitter() const { return _jitter; }
    void setJitter(int jitter);
    int eraser() const { return _eraser; }
    void setEraser(int eraser);

    bool isTouch() const { return _isTouch; }
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
    QColor _color = QColor(Qt::black);
    int _size = 30;
    int _hardness = 80;
    int _opacity = 80;
    int _flow = 100;
    int _roundness = 100;
    int _angle = 0;
    int _spacing = 100;
    int _jitter = 0;
    int _eraser = 0;

    bool _isTouch = false;
    CanvasItem* _canvasItem;
    CanvasItem* _canvasBuffer;

    QPointF _startPoint;
    QPointF _lastPoint;
    QPoint _topleft;
    QPoint _bottomright;
    QByteArray _undoImage;
    QByteArray _redoImage;
    void paintDab(const QPointF& point, QPainter& painter);
};
