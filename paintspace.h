#ifndef PAINTSPACE_H
#define PAINTSPACE_H

#include <QQuickPaintedItem>
#include <QPixmap>
#include <QColor>
#include <QPainter>

class PaintSpace : public QQuickPaintedItem
{
    Q_OBJECT

    Q_PROPERTY(QColor color READ color WRITE setColor NOTIFY colorChanged)
    Q_PROPERTY(int width READ width WRITE setWidth NOTIFY widthChanged)
    Q_PROPERTY(int height READ height WRITE setHeight NOTIFY heigthChanged)

public:
    explicit PaintSpace(QQuickPaintedItem *parent = 0);
    void paint(QPainter *painter);
    //void paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *);
    void setColor(const QColor color);
    QColor color() {return pixmapColor;}
    void setWidth(const int width); // {pixmapWidth = width;}
    int width() {return pixmapWidth;}
    void setHeight(const int height);// {pixmapHeight = height;}
    int height() {return pixmapHeight;}
    
signals:
    void colorChanged();
    void widthChanged();
    void heigthChanged();

public slots:

private:
    QPixmap *pixmap;
    QColor pixmapColor;
    int pixmapWidth;
    int pixmapHeight;
    void createPixmap();
};

#endif // PAINTSPACE_H
