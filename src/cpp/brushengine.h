#pragma once
#include <QtCore>
#include "canvasitem.h"

class BrushEngine : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QColor color READ color WRITE setColor NOTIFY colorChanged)
    Q_PROPERTY(int size READ size WRITE setSize NOTIFY sizeChanged)
    Q_PROPERTY(int hardness READ hardness WRITE setHardness NOTIFY hardnessChanged)
    Q_PROPERTY(int opacity READ opacity WRITE setOpacity NOTIFY opacityChanged)
    Q_PROPERTY(int roundness READ roundness WRITE setRoundness NOTIFY roundnessChanged)

public:
    BrushEngine() {}
    Q_INVOKABLE void paint(const QPointF& point, CanvasItem* canvasItem, float pressure=1.0);
    QColor color() const { return m_color; }
    void setColor(QColor color);
    int size() const { return m_size; }
    void setSize(int size);
    int hardness() const { return m_hardness; }
    void setHardness(int hardness);
    int opacity() const { return m_opacity; }
    void setOpacity(int opacity);
    int roundness() const { return m_roundness; }
    void setRoundness(int roundness);

signals:
    void colorChanged(QColor color);
    void sizeChanged(int size);

    void hardnessChanged(int hardness);

    void opacityChanged(int opacity);

    void roundnessChanged(int roundness);

private:
    QColor m_color = QColor(Qt::black);
    int m_size = 30;
    int m_hardness = 80;
    int m_opacity = 80;
    int m_roundness;
};
