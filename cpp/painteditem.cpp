#include "painteditem.h"
#include "brushengine.h"
#include <QDebug>

PaintedItem::PaintedItem(QQuickItem *parent) :
    QQuickPaintedItem(parent)
{
}

void PaintedItem::paint(QPainter *painter)
{
    if (pixmap.isNull())
    {
        pixmap = QPixmap(contentsSize());
        pixmap.fill(fillColor());
    }
    painter->drawPixmap(0, 0, pixmap);
    //pixmap.save("D:\pix.png");
    //qDebug() << "update " << this;
}


