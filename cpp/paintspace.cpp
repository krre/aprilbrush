#include "paintspace.h"
#include "brushengine.h"
#include <QDebug>

PaintSpace::PaintSpace(QQuickItem *parent) :
    QQuickPaintedItem(parent)
{
}

void PaintSpace::paint(QPainter *painter)
{
    if (pixmap.isNull())
    {
        pixmap = QPixmap(contentsSize());
        pixmap.fill(fillColor());
    }
    painter->drawPixmap(0, 0, pixmap);
    //qDebug() << this;
}


