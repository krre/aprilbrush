#include "paintspace.h"
#include "brushengine.h"
#include <QDebug>

QHash<long, PaintSpace*> PaintSpace::paintItemHash;
QHash<long, QPixmap*> PaintSpace::pixmapHash;

PaintSpace::PaintSpace(QQuickItem *parent) :
    QQuickPaintedItem(parent)
{
}

void PaintSpace::paint(QPainter *painter)
{
    if (!pixmapHash.contains(hashPageLayer))
    {
        pixmap = new QPixmap(contentsSize());
        pixmap->fill(fillColor());
        pixmapHash[hashPageLayer] = pixmap;
        BrushEngine::pixmap = pixmap;
    }

    paintItemHash[hashPageLayer] = this;
    pixmap = pixmapHash[hashPageLayer];
    painter->drawPixmap(0, 0, *pixmap);
}


