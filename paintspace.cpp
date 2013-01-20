#include "paintspace.h"

PaintSpace::PaintSpace(QDeclarativeItem *parent) :
    QDeclarativeItem(parent)
{
    setFlag(QGraphicsItem::ItemHasNoContents, false);

    int screenWidth = qApp->desktop()->width();
    int screenHeigth = qApp->desktop()->height();
    pixmap = new QPixmap(screenWidth, screenHeigth);
    pixmapColor.setAlpha(0);
    pixmap->fill(pixmapColor);
}

void PaintSpace::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    painter->drawPixmap(0, 0, *pixmap);
    //painter->drawLine(qrand()%1000, qrand()%100, qrand()%100, qrand()%100);
}

void PaintSpace::setColor(const QColor color)
{
    pixmapColor = color;
    pixmap->fill(pixmapColor);
    update();
    emit colorChanged();
}

QColor PaintSpace::color()
{
    return pixmapColor;
}
