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
    QImage* image() { return m_image; }

protected:
    void paint(QPainter * painter);
    void geometryChanged(const QRectF & newGeometry, const QRectF & oldGeometry);

signals:

private:
    QImage *m_image;

};

#endif // CANVASITEM_H
