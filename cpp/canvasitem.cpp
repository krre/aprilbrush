#include "canvasitem.h"
#include <QtCore>
#include <QtGui>

CanvasItem::CanvasItem(QQuickPaintedItem *parent) :
    QQuickPaintedItem(parent)
{
}

CanvasItem::~CanvasItem()
{
    delete m_pixmap;
}

void CanvasItem::clear(QColor color)
{
    m_pixmap->fill(color);
    update();
}

void CanvasItem::paint(QPainter *painter)
{
    painter->drawPixmap(0, 0, *m_pixmap);
}

void CanvasItem::geometryChanged(const QRectF &newGeometry, const QRectF &oldGeometry)
{
    if (newGeometry.width() && newGeometry.height()) {
        m_pixmap = new QPixmap(width(), height());
        clear();
    }
}
