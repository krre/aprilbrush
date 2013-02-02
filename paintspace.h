#ifndef PAINTSPACE_H
#define PAINTSPACE_H

//#include <QDeclarativeItem>
#include <QQuickItem>
//#include <QtWidgets>

class PaintSpace : public QQuickItem
{
    Q_OBJECT
    Q_PROPERTY(QColor color READ color WRITE setColor NOTIFY colorChanged)

public:
    explicit PaintSpace(QQuickItem *parent = 0);
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *);
    void setColor(const QColor color);
    QColor color();


    
signals:
    void colorChanged();
    
public slots:

private:
    QPixmap *pixmap;
    QColor pixmapColor;
};

#endif // PAINTSPACE_H
