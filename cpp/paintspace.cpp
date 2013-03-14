#include "paintspace.h"
#include "brushengine.h"
#include <QDebug>

QHash<long, QQuickPaintedItem*> PaintSpace::paintItemHash;
QHash<long, QPixmap*> PaintSpace::pixmapHash;

PaintSpace::PaintSpace(QQuickItem *parent) :
    QQuickPaintedItem(parent)
{
}

void PaintSpace::paint(QPainter *painter)
{
    //qDebug() << pixmapHash.contains(hashPixmap);
    if (!pixmapHash.contains(hashPixmap))
    //if (pixmap.isNull())
    {
        pixmap = new QPixmap(contentsSize());
        pixmap->fill(fillColor());
        paintItemHash[hashPixmap] = this;
        pixmapHash[hashPixmap] = pixmap;
        BrushEngine::pixmap = pixmap;
        BrushEngine::paintedLayer = this;
        //qDebug() << paintItemHash;
        //qDebug() << pixmapHash;

    }
    pixmap = pixmapHash[hashPixmap];
    qDebug() << pixmap << hashPixmap;
    painter->drawPixmap(0, 0, *pixmap);
}


