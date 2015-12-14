#include "canvasitem.h"

CanvasItem::CanvasItem()
{
//    setRenderTarget(QQuickPaintedItem::FramebufferObject);
}

CanvasItem::~CanvasItem()
{
    delete m_pixmap;
}

void CanvasItem::paint(QPainter* painter)
{
    painter->drawPixmap(0, 0, *m_pixmap);
}

void CanvasItem::clear()
{
    m_pixmap->fill(Qt::transparent);
    update();
}

void CanvasItem::setSize(QSize size)
{
    if (m_size == size) return;
    m_size = size;
    m_pixmap = new QPixmap(size);
    m_pixmap->fill(Qt::transparent);

    emit sizeChanged(size);
}
