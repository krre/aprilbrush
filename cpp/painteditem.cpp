#include "painteditem.h"
#include <QDebug>

PaintedItem::PaintedItem(QQuickItem *parent) :
    QQuickPaintedItem(parent)
{
    //qDebug() << "new " << this << "objName" << objectName();
    pixmap = 0;
}

void PaintedItem::paint(QPainter *painter)
{
    if (!pixmap)
    {
        pixmap = m_imageProcessor->pixmapHash()[objectName()];
    }

    painter->drawPixmap(0, 0, *pixmap);
    //qDebug() << pixmap << m_imageProcessor << objectName() << m_imageProcessor->pixmapHash()[objectName()];
}
