#pragma once
#include <QtCore>
#include "canvasitem.h"

class BrushEngine : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QColor color READ color WRITE setColor NOTIFY colorChanged)
    Q_PROPERTY(int size READ size WRITE setSize NOTIFY sizeChanged)

public:
    BrushEngine() {}
    Q_INVOKABLE void paint(float x, float y, CanvasItem* canvasItem, float pressure=1.0);
    QColor color() const { return m_color; }
    void setColor(QColor color);
    int size() const { return m_size; }
    void setSize(int size);

signals:
    void colorChanged(QColor color);
    void sizeChanged(int size);

private:
    QColor m_color = QColor(Qt::black);
    int m_size = 30;
};
