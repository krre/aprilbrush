#include "canvasitem.h"
#include <QtCore>
#include <QtGui>

CanvasItem::CanvasItem(QQuickPaintedItem *parent) :
    QQuickPaintedItem(parent)
{
    connect(this, SIGNAL(widthChanged()), this, SLOT(changeCanvasSize()));
}

CanvasItem::~CanvasItem()
{
    delete pixmap;
}

void CanvasItem::clear(QColor color)
{
    pixmap->fill(color);
}

void CanvasItem::paint(QPainter *painter)
{
    painter->drawPixmap(0, 0, *pixmap);
}

void CanvasItem::changeCanvasSize()
{
    pixmap = new QPixmap(width(), height());
    clear();
}
