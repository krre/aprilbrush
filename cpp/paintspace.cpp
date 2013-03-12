#include "paintspace.h"
#include "brushengine.h"

QList<QQuickPaintedItem*> PaintSpace::paintItemList;
QList<QPixmap*> PaintSpace::pixmapList;

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
        paintItemList.append(this);
        pixmapList.append(&pixmap);
        BrushEngine::pixmap = &pixmap;
        BrushEngine::paintedLayer = this;

    }

    painter->drawPixmap(0, 0, pixmap);
}


