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
    static QHash<long, PaintSpace*> paintItemHash;
    static QHash<long, QPixmap*> pixmapHash;
    
public slots:

private:
    inline long hash() { return hashPageLayer; }
    inline void setHash(long hash) { hashPageLayer = hash; }

    QPixmap *pixmap;
    long hashPageLayer;
};

#endif // PAINTSPACE_H
