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
    delete m_pixmap;
}

void CanvasItem::clear(QColor color)
{
    m_pixmap->fill(color);
}

void CanvasItem::paint(QPainter *painter)
{
    painter->drawPixmap(0, 0, *m_pixmap);
}

void CanvasItem::changeCanvasSize()
{
    m_pixmap = new QPixmap(width(), height());
    clear();
}
