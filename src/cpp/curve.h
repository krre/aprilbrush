#ifndef CURVE_H
#define CURVE_H

#include <QtGui>

class Curve : public QObject
{
    Q_OBJECT
public:
    explicit Curve(QObject *parent = 0);
    Q_INVOKABLE void reset(QPointF startPoint);
    Q_INVOKABLE void lineTo(QPointF point);
    Q_INVOKABLE void quadTo(QPointF ctrlPoint, QPointF endPoint);
    Q_INVOKABLE qreal length();
    Q_INVOKABLE QPointF pointAtLength(qreal length);

signals:

public slots:

private:
    QPainterPath painterPath;
};

#endif // CURVE_H
