#pragma once
#include <QtCore>
#include "canvasitem.h"

class BrushEngine : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QColor color READ color WRITE setColor NOTIFY colorChanged)
public:
    BrushEngine() {}
    Q_INVOKABLE void paint(float x, float y, CanvasItem* canvasItem, float pressure=1.0);
    QColor color() const { return m_color; }

    void setColor(QColor color);

signals:
    void colorChanged(QColor color);

private:
    QColor m_color = QColor(Qt::black);
};
