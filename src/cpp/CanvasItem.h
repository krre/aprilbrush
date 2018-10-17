#pragma once
#include <QQuickPaintedItem>
#include <QScopedPointer>

class CanvasItem : public QQuickPaintedItem {
    Q_OBJECT
    Q_PROPERTY(QSize size READ getSize WRITE setSize NOTIFY sizeChanged)
public:
    CanvasItem();
    ~CanvasItem();
    void paint(QPainter* painter) override;
    QSize getSize() const { return size; }
    void setSize(QSize size);
    QPixmap* getPixmap() const { return pixmap.data(); }
    Q_INVOKABLE void clear();
    Q_INVOKABLE QPointF getItemPos(const QPointF& point) { return mapFromScene(point); }
    Q_INVOKABLE void drawImage(const QByteArray& getImage);
    Q_INVOKABLE QByteArray getImage(QPoint topleft = QPoint(), QPoint bottomright = QPoint());
    Q_INVOKABLE void setImage(const QByteArray& getImage, QPoint topleft = QPoint());

signals:
    void sizeChanged(QSize size);

private:
    QSize size;
    QScopedPointer<QPixmap> pixmap;
};
