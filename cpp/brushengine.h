#pragma once
#include <QtCore>
#include "canvasitem.h"

class BrushEngine : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QColor color READ color WRITE setColor NOTIFY colorChanged)
    Q_PROPERTY(int size READ size WRITE setSize NOTIFY sizeChanged)
    Q_PROPERTY(int hardness READ hardness WRITE setHardness NOTIFY hardnessChanged)

public:
    BrushEngine() {}
    Q_INVOKABLE void paint(float x, float y, CanvasItem* canvasItem, float pressure=1.0);
    QColor color() const { return m_color; }
    void setColor(QColor color);
    int size() const { return m_size; }
    void setSize(int size);
    int hardness() const { return m_hardness; }
    void setHardness(int hardness);

signals:
    void colorChanged(QColor color);
    void sizeChanged(int size);

    void hardnessChanged(int hardness);

private:
    QColor m_color = QColor(Qt::black);
    int m_size = 30;
    int m_hardness = 80;
};
