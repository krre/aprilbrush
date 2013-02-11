#ifndef PAINTSPACE_H
#define PAINTSPACE_H

#include <QQuickPaintedItem>
#include <QtGui>

class PaintSpace : public QQuickPaintedItem
{
    Q_OBJECT

    Q_PROPERTY(QColor color READ color WRITE setColor NOTIFY colorChanged)

public:
    PaintSpace(QQuickItem *parent = 0);
    void paint(QPainter *painter);
    void setColor(const QColor color) {pixmapColor = color;}
    QColor color() {return pixmapColor;}
    
signals:
    void colorChanged();

public slots:

private:
    QPixmap pixmap;
    QColor pixmapColor;
};


#endif // PAINTSPACE_H
