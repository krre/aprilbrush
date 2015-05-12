import QtQuick 2.4

QtObject {
    property bool isTouch: false
    property Canvas canvas

    function paint(point, pressure) {

    }
}

/*

#include "brushengine.h"

BrushEngine::BrushEngine(QObject *parent) :
    QObject(parent)
{
}

void BrushEngine::setTouch(bool isTouch, CanvasItem *canvas)
{
    if (isTouch) {
        this->canvas = canvas;
        isFirstPoint = true;
    }
}

void BrushEngine::setSize(int size)
{
     m_size = size;
     setDeltaDab();
     dabImage = QImage(size, size, QImage::Format_ARGB32);
     dabImage.fill(Qt::transparent);
     QPainter dabPainter(&dabImage);
     dabPainter.setRenderHint(QPainter::Antialiasing, true);
     dabPainter.setPen(Qt::NoPen);
     dabPainter.setBrush(QBrush(m_color));
     if (m_size > 1) {
         dabPainter.drawEllipse(0, 0, m_size, m_size);
     } else {
         dabPainter.drawRect(0, 0, 1, 1);
     }
}

void BrushEngine::paint(QPointF point, qreal pressure)
{
    if (isFirstPoint) {
        paintDab(point, pressure);
        points.clear();
        points.append(point);
        lastDrawPoint = point;
        controlPoint = QPointF();
        isFirstPoint = false;
    } else {
        paintDab(point, pressure);
        return;
        startPoint = lastDrawPoint;
        qreal deltaPoint = qSqrt(qPow(startPoint.x() - point.x(), 2) + qPow(startPoint.y() - point.y(), 2));
        int numDabs = qFloor(deltaPoint / deltaDab);
        if (numDabs >= 1) {
            if (points.length() == 1 || numDabs < 3 || !isBezier) {
                endPoint = point;
            } else {
                controlPoint = points.at(points.length() - 1);
                endPoint = (controlPoint + point) / 2;
            }
            qreal deltaT = 1.0 / numDabs;
            betweenPoint = startPoint;
            qreal t = deltaT;
            qreal diff = 0;
            QPointF curvePoint;
            while (t > 0 && t <= 1) {
                curvePoint = controlPoint.isNull() ? linearCurve(startPoint, endPoint, t) : bezierCurve(startPoint, endPoint, controlPoint, t);
                deltaPoint = qSqrt(qPow(curvePoint.x() - betweenPoint.x(), 2) + qPow(curvePoint.y() - betweenPoint.y(), 2));
                if (diff && qAbs(deltaPoint - deltaDab) > qAbs(diff)) { break; } // check on bezier loop
                diff = deltaPoint - deltaDab;
                if (qAbs(diff) <= 0.5) {
                    paintDab(curvePoint, pressure);
                    diff = 0;
                    betweenPoint = curvePoint;
                    t += deltaT;
                } else {
                    t -= diff / deltaDab * deltaT;
                }
            }

            points.append(point);
            lastDrawPoint = betweenPoint;
            controlPoint = QPointF();
        }
    }
}

void BrushEngine::paintDab(QPointF point, qreal pressure)
{

//    qDebug() << pressure;
    QPainter painter(canvas->image());
    painter.setRenderHint(QPainter::Antialiasing, true);
    painter.setPen(Qt::NoPen);
    painter.setBrush(QBrush(m_color));
    painter.setOpacity(m_opacity / 100.0 * pressure);
    QRectF rect;
    if (m_size > 1) {
        rect = QRectF(QPointF(point.x() - m_size / 2.0, point.y() - m_size / 2.0), QSizeF(m_size, m_size));
        painter.drawEllipse(rect);
    } else {
        rect = QRectF(point.x() - 0.5, point.y() - 0.5, 1, 1);
        painter.drawRect(rect);
    }
    painted(rect);
}

void BrushEngine::setDeltaDab()
{
    deltaDab = qMax(m_spacing / 100.0 * m_size, 1.0);
}

QPointF BrushEngine::linearCurve(QPointF start, QPointF end, qreal t)
{
    qreal x = (1 - t) * start.x() + t * end.x();
    qreal y = (1 - t) * start.y() + t * end.y();
    return QPointF(x, y);
}

QPointF BrushEngine::bezierCurve(QPointF start, QPointF end, QPointF control, qreal t)
{
    qreal x = qPow((1 - t), 2) * start.x() + 2 * t * (1 - t) * control.x() + t * t * end.x();
    qreal y = qPow((1 - t), 2) * start.y() + 2 * t * (1 - t) * control.y() + t * t * end.y();
    return QPointF(x, y);
}


*/

