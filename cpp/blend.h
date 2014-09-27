#ifndef BLEND_H
#define BLEND_H

#include <QtGui>

class Blend : public QObject
{
    Q_OBJECT
public:
    explicit Blend(QObject *parent = 0);
    static void alphaMax(const QImage& src, QImage& dst, const QPointF& coord, qreal factor);

signals:

public slots:

};

#endif // BLEND_H
