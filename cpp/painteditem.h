#ifndef PAINTSPACE_H
#define PAINTSPACE_H

#include <QQuickPaintedItem>
#include <QtGui>

class PaintedItem : public QQuickPaintedItem
{
    Q_OBJECT
    Q_PROPERTY(QPixmap pixmap READ pixmap WRITE setPixmap)

public:
    PaintedItem(QQuickItem *parent = 0);
    void paint(QPainter *painter);
    QPixmap pixmapItem;

private:
    inline QPixmap pixmap() { return pixmapItem; }
    inline void setPixmap(QPixmap pixmap) { pixmapItem = pixmap; }
};

#endif // PAINTSPACE_H
