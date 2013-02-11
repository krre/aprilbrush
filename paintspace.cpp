#include "paintspace.h"
#include <QDebug>

PaintSpace::PaintSpace(QQuickPaintedItem *parent) :
    QQuickPaintedItem(parent)
{
    //setFlag(QGraphicsItem::ItemHasNoContents, false);

    //int screenWidth = qApp->desktop()->width();
    //int screenHeigth = qApp->desktop()->height();
    //pixmapWidth = 0;
    //pixmapHeight = 0;
    //pixmap = new QPixmap(pixmapWidth, pixmapHeight);
    pixmap = new QPixmap(0, 0);
    pixmapColor.setAlpha(0);

    //qDebug() << pixmapWidth << pixmapHeight << pixmapColor;
    qDebug() << "constructor";

}

void PaintSpace::paint(QPainter *painter)
{
    painter->drawPixmap(0, 0, *pixmap);
    //painter->drawLine(qrand()%1000, qrand()%100, qrand()%100, qrand()%100);
}

void PaintSpace::setColor(const QColor color)
{
    pixmapColor = color;
    createPixmap();
    //pixmap->fill(pixmapColor);
    qDebug() << "color: " << pixmapColor;


    //emit colorChanged();
    //qDebug() << "set color: " << pixmapColor;
    //qDebug() << pixmapWidth << pixmapHeight << pixmapColor;
}

void PaintSpace::setWidth(const int width)
{
    pixmapWidth = width;
    createPixmap();
//    if (pixmapHeight)
//        createPixmap();
    qDebug() << "width: " << pixmapWidth;
}

void PaintSpace::setHeight(const int height)
{
    pixmapHeight = height;
    createPixmap();
//    if (pixmapWidth)
//        createPixmap();
    qDebug() << "height: " << pixmapHeight;
}

void PaintSpace::createPixmap()
{
    //pixmap = new QPixmap(pixmapWidth, pixmapHeight);
    if (pixmapWidth && pixmapHeight)
    {
    pixmap->scaled(pixmapWidth, pixmapHeight);
    pixmap->fill(pixmapColor);
    update();

    pixmap->save("D:/pixmap.png");
    qDebug() << pixmap->width() << pixmap->height() << pixmapColor;
    }
}


