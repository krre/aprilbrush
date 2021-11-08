#pragma once
#include <QObject>
#include <QColor>
#include <QPointF>

class QPainter;
class Layer;

class BrushEngine : public QObject {
    Q_OBJECT
public:
    BrushEngine(QObject* parent);

    void paint(QPixmap* pixmap, const QPointF& point, float pressure = 1.0);

//    void setLayer(Layer* layer);
//    void setLayerBuffer(Layer* layerBuffer);

//    const QByteArray& undoImage() const;
//    const QByteArray& redoImage() const;

    QPointF startPos() { return topleft; }

    const QColor& color() const;

    int size() const;
    void setSize(int size);

    int hardness() const;
    void setHardness(int hardness);

    int opacity() const;
    void setOpacity(int opacity);

    int flow() const;
    void setFlow(int flow);

    int roundness() const;
    void setRoundness(int roundness);

    int angle() const;
    void setAngle(int angle);

    int spacing() const;
    void setSpacing(int spacing);

    int jitter() const;
    void setJitter(int jitter);

    int eraser() const;
    void setEraser(int eraser);

//    bool getIsTouch() const { return m_isTouch; }
//    void setIsTouch(bool isTouch);

public slots:
    void setColor(const QColor& color);

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

//    void isTouchChanged(bool isTouch);

private:
    void paintDab(const QPointF& point, QPainter& painter);

    QColor m_color = QColor(Qt::black);
    int m_size = 30;
    int m_hardness = 80;
    int m_opacity = 80;
    int m_flow = 100;
    int m_roundness = 100;
    int m_angle = 0;
    int m_spacing = 100;
    int m_jitter = 0;
    int m_eraser = 0;

//    bool m_isTouch = false;
//    Layer* m_layer;
//    Layer* m_layerBuffer;

    QPointF startPoint;
    QPointF lastPoint;
    QPoint topleft;
    QPoint bottomright;
//    QByteArray m_undoImage;
//    QByteArray m_redoImage;
};
