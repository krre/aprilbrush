#include "brushengine.h"

BrushEngine::BrushEngine(QObject *parent) :
    QObject(parent)
{
}

void BrushEngine::setTouch(bool isTouch, CanvasItem *canvas)
{
    if (isTouch) {
        this->canvas = canvas;
    } else {
        path = QPainterPath();
    }
}

void BrushEngine::paint(QPointF point, qreal pressure)
{
    if (!path.elementCount()) {
        path.moveTo(point);
        prevPoint = point;
        strokeLength = 0;
        paintDab(point, pressure);
    } else {
        qreal deltaPoint = qSqrt(qPow(prevPoint.x() - point.x(), 2) + qPow(prevPoint.y() - point.y(), 2));
        qreal deltaDab = m_size * m_spacing / 100.0;
        int numDabs = qFloor(deltaPoint / deltaDab);
        if (numDabs >= 1) {
            if (deltaPoint >= deltaDab && isBezier) {
                path.quadTo(prevPoint.x(), prevPoint.y(), (prevPoint.x() + point.x()) / 2.0, (prevPoint.y() + point.y()) / 2.0);
            } else {
                path.lineTo(point);
            }

            qreal pathLength = path.length();
            while(pathLength >= strokeLength) {
                if (pathLength > 0) {
                    paintDab(path.pointAtPercent(strokeLength / pathLength), pressure);
                }
                strokeLength += deltaDab;
            }

            prevPoint = point;
        }
    }
}

void BrushEngine::paintDab(QPointF point, qreal pressure)
{
    QPixmap *pixmap = canvas->pixmap();
    qDebug() << "paint" << point;
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
