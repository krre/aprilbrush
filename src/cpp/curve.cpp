#include "curve.h"

Curve::Curve(QObject *parent) :
    QObject(parent)
{
}

void Curve::reset(QPointF startPoint)
{
    painterPath = QPainterPath(startPoint);
}

void Curve::lineTo(QPointF point)
{
    if (painterPath.elementCount() > 1) {
        QPainterPath::Element element = painterPath.elementAt(1);
        painterPath = QPainterPath(QPointF(element.x, element.y));
    }
    painterPath.lineTo(point);
}

void Curve::quadTo(QPointF ctrlPoint, QPointF endPoint)
{
    if (painterPath.elementCount() > 1) {
        QPainterPath::Element element = painterPath.elementAt(1);
        painterPath = QPainterPath(QPointF(element.x, element.y));
    }
    painterPath.quadTo(ctrlPoint, endPoint);
}

qreal Curve::length()
{
    return painterPath.length();
}

QPointF Curve::pointAtLength(qreal length)
{
    return painterPath.pointAtPercent(length / painterPath.length());
}

