#pragma once
#include <QObject>
#include <QColor>
#include <QPointF>
#include <QSize>
#include <QRect>

class QPainter;
class Layer;

class BrushEngine : public QObject {
    Q_OBJECT
public:
    BrushEngine(QObject* parent);

    QRect paint(QPixmap* pixmap, const QPointF& point, float pressure = 1.0);
    void finish();
    const QRect& bound() const;

    const QColor& color() const;
    int size() const;
    int hardness() const;
    void setHardness(int hardness);
    int opacity() const;
    int flow() const;
    int roundness() const;
    int angle() const;
    int spacing() const;
    int jitter() const;
    int eraser() const;

public slots:
    void setColor(const QColor& color);
    void setSize(int size);
    void setOpacity(int opacity);
    void setFlow(int flow);
    void setRoundness(int roundness);
    void setAngle(int angle);
    void setSpacing(int spacing);
    void setJitter(int jitter);
    void setEraser(int eraser);

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

private:
    void paintDab(const QPointF& point, QPainter& painter);
    qreal jitterOffset();

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

    QPointF m_startPoint;
    QPointF m_lastPoint;
    QRect m_dabRect;
};
