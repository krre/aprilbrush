#pragma once
#include <QObject>
#include <QColor>
#include <QPointF>

class QPainter;
class Layer;

class BrushEngine : public QObject {
    Q_OBJECT
public:
    void paint(const QPointF& point, float pressure = 1.0);

    void setLayer(Layer* layer);
    void setCanvasBuffer(Layer* layerBuffer);

    const QByteArray& undoImage() const;
    const QByteArray& redoImage() const;

    QPointF startPos() { return topleft; }

    const QColor& color() const;
    void setColor(const QColor& color);

    uint size() const;
    void setSize(uint size);

    uint hardness() const;
    void setHardness(uint hardness);

    uint opacity() const;
    void setOpacity(uint opacity);

    uint flow() const;
    void setFlow(uint flow);

    uint roundness() const;
    void setRoundness(uint roundness);

    uint angle() const;
    void setAngle(uint angle);

    uint spacing() const;
    void setSpacing(uint spacing);

    uint jitter() const;
    void setJitter(uint jitter);

    int eraser() const;
    void setEraser(uint eraser);

    bool getIsTouch() const { return m_isTouch; }
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

    QColor m_color = QColor(Qt::black);
    uint m_size = 30;
    uint m_hardness = 80;
    uint m_opacity = 80;
    uint m_flow = 100;
    uint m_roundness = 100;
    uint m_angle = 0;
    uint m_spacing = 100;
    uint m_jitter = 0;
    uint m_eraser = 0;

    bool m_isTouch = false;
    Layer* m_layer;
    Layer* m_layerBuffer;

    QPointF startPoint;
    QPointF lastPoint;
    QPoint topleft;
    QPoint bottomright;
    QByteArray m_undoImage;
    QByteArray m_redoImage;
};
