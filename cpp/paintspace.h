#ifndef PAINTSPACE_H
#define PAINTSPACE_H

#include <QQuickPaintedItem>
#include <QtGui>

class PaintSpace : public QQuickPaintedItem
{
    Q_OBJECT
    // Number in format xxxyyy where xxx is page, yyy is layer
    Q_PROPERTY(long hash READ hash WRITE setHash)

public:
    PaintSpace(QQuickItem *parent = 0);
    void paint(QPainter *painter);
    static QHash<long, QQuickPaintedItem*> paintItemHash;
    static QHash<long, QPixmap*> pixmapHash;
    
public slots:

private:
    inline long hash() { return hashPixmap; }
    inline void setHash(long hash) { hashPixmap = hash; }

    QPixmap *pixmap;
    long hashPixmap;
};

#endif // PAINTSPACE_H
