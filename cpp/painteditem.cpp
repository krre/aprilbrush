#include "painteditem.h"
#include <QDebug>

PaintedItem::PaintedItem(QQuickItem *parent) :
    QQuickPaintedItem(parent)
{
    qDebug() << "new " << this;
}

void PaintedItem::paint(QPainter *painter)
{
    if (pixmapItem.isNull())
    {
        pixmapItem = QPixmap(contentsSize());
        pixmapItem.fill(fillColor());
        //pixmapItem.fill(Qt::red);
        //update();
    }

    painter->drawPixmap(0, 0, pixmapItem);
    qDebug() << "paint" << this;
    //pixmapItem.save("d:/pix.png");
}

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


