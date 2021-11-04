#pragma once
#include <QWidget>
#include <QScopedPointer>
#include <QPixmap>

class Layer : public QWidget {
    Q_OBJECT
public:
    Layer() = default;
    void paint(QPainter* painter);

    const QSize& size() const;
    void setSize(QSize size);

    QPixmap* pixmap() const;
    void clear();
//    QPointF getItemPos(const QPointF& point) { return mapFromScene(point); }
    void drawImage(const QByteArray& image);

    QByteArray image(QPoint topleft = QPoint(), QPoint bottomright = QPoint());
    void setImage(const QByteArray& getImage, QPoint topleft = QPoint());

signals:
    void sizeChanged(QSize size);

private:
    QSize m_size;
    QScopedPointer<QPixmap> m_pixmap;
};
