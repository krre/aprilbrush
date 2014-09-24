#include "brushengine.h"

BrushEngine::BrushEngine(QObject *parent) :
    QObject(parent)
{
}

void BrushEngine::paint(QPointF point, CanvasItem *canvas, qreal pressure)
{
    this->canvas = canvas;
    paintDab(point, pressure);
}

void BrushEngine::setTouch(bool isTouch, QPointF point)
{
    this->isTouch = isTouch;
    if (isTouch) {
        path = new QPainterPath(point);
        prevPoint = point;
    } else {
        delete path;
    }
}

void BrushEngine::paintDab(QPointF point, qreal pressure)
{
    QPixmap *pixmap = canvas->pixmap();

    QPainter painter(pixmap);
    painter.setRenderHint(QPainter::Antialiasing, true);
    painter.setPen(Qt::NoPen);
    painter.setBrush(QBrush(m_color));
    painter.setOpacity(m_opacity / 100.0 * pressure);

    if (m_size > 1) {
        painter.drawEllipse(point, m_size / 2, m_size / 2);
    } else {
        painter.drawRect(QRectF(point.x() - 0.5, point.y() - 0.5, 1, 1));
    }
    painted();
}
