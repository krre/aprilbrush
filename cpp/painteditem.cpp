#include "painteditem.h"
#include <QDebug>

PaintedItem::PaintedItem(QQuickItem *parent) : QQuickPaintedItem(parent)
{
    pixmap = 0;
}

void PaintedItem::paint(QPainter *painter)
{
    if (!pixmap)
        pixmap = m_imageProcessor->pixmapHash()[objectName()];

    painter->drawPixmap(0, 0, *pixmap);
}
