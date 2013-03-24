#include "painteditem.h"
#include <QDebug>

PaintedItem::PaintedItem(QQuickItem *parent) :
    QQuickPaintedItem(parent)
{
}

void PaintedItem::paint(QPainter *painter)
{
    if (pixmapItem.isNull())
    {
        pixmapItem = QPixmap(contentsSize());
        pixmapItem.fill(fillColor());
    }

    painter->drawPixmap(0, 0, pixmapItem);
}

void PaintedItem::setPixmapArea(QPoint startPos, QByteArray area)
{
    QPixmap pixmap;
    pixmap.loadFromData(qUncompress(area));

    qDebug() << "paintedItem " << startPos << pixmap << area.size();

    QPainter painter(&pixmapItem);
    painter.setCompositionMode(QPainter::CompositionMode_Source);
    painter.fillRect(QRect(startPos, pixmap.size()), Qt::transparent);
    painter.setCompositionMode(QPainter::CompositionMode_SourceOver);
    painter.drawPixmap(startPos.x(), startPos.y(), pixmap);

    //pixmap.save("d:/pix.png");

    update();
}


