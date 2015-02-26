#include "canvasItem.h"
#include <QtCore>
#include <QtGui>

CanvasItem::CanvasItem(QQuickPaintedItem *parent) :
    QQuickPaintedItem(parent)
{
}

CanvasItem::~CanvasItem()
{
    delete m_image;
}

void CanvasItem::clear(QColor color)
{
    m_image->fill(color);
    update();
}

void CanvasItem::paint(QPainter *painter)
{
    painter->drawImage(0, 0, *m_image);
}

void CanvasItem::geometryChanged(const QRectF &newGeometry, const QRectF &oldGeometry)
{
    Q_UNUSED(oldGeometry)
    if (newGeometry.width() && newGeometry.height()) {
        m_image = new QImage(width(), height(), QImage::Format_ARGB32);
        clear();
    }
}
