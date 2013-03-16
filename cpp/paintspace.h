#ifndef PAINTSPACE_H
#define PAINTSPACE_H

#include <QQuickPaintedItem>
#include <QtGui>

class PaintSpace : public QQuickPaintedItem
{
    Q_OBJECT

public:
    PaintSpace(QQuickItem *parent = 0);
    void paint(QPainter *painter);
    QPixmap pixmap;
};

#endif // PAINTSPACE_H
