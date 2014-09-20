#ifndef CANVASITEM_H
#define CANVASITEM_H

#include <QtQuick>

class CanvasItem : public QQuickPaintedItem
{
    Q_OBJECT
public:
    explicit CanvasItem(QQuickPaintedItem *parent = 0);
    ~CanvasItem();
    Q_INVOKABLE void clear(QColor color=Qt::transparent);

protected:
    void paint(QPainter * painter);

signals:

private slots:
    void changeCanvasSize();

private:
    QPixmap *pixmap;

};

#endif // CANVASITEM_H
