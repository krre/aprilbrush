#include "painteditem.h"
#include "brushengine.h"
#include <QDebug>

PaintedItem::PaintedItem(QQuickItem *parent) :
    QQuickPaintedItem(parent)
{
}

void PaintedItem::paint(QPainter *painter)
{
    if (pixmapItem.isNull())
    {
        pixmapItem = QPixmap(contentsSize());
        pixmapItem.fill(fillColor());
    }
    painter->drawPixmap(0, 0, pixmapItem);
    //pixmap.save("D:\pix.png");
    //qDebug() << "update " << this;
}


