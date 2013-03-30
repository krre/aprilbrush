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
/*
void PaintedItem::setPixmapArea(QPoint startPos, QByteArray area)
{
    QPixmap pixmap;
    pixmap.loadFromData(qUncompress(area));

    if ((startPos.x()) != 0 && (startPos.y() != 0))
    {
        QPainter painter(&pixmapItem);
        painter.setCompositionMode(QPainter::CompositionMode_Source);
        painter.fillRect(QRect(startPos, pixmap.size()), Qt::transparent);
        painter.setCompositionMode(QPainter::CompositionMode_SourceOver);
        painter.drawPixmap(startPos.x(), startPos.y(), pixmap);
    }
    else
        pixmapItem = QPixmap(pixmap);

    //qDebug() << "paintedItem " << startPos << pixmap << area.size() << pixmapItem << this;
    //qDebug() << "painedItem " << this;

    //pixmapItem.save("d:/pix.png");

    update();
}

*/
