#pragma once
#include <QScopedPointer>
#include <QSize>
#include <QPoint>

class QPixmap;

class Layer {
public:
    Layer(const QString& name, const QSize& size);
    ~Layer();

    void setName(const QString& name);
    const QString& name() const;

    const QSize& size() const;
    void setSize(QSize size);

    QPixmap* pixmap() const;
    void clear();

    QByteArray image(const QPoint& topLeft = QPoint(), const QPoint& bottomRight = QPoint());
    void setImage(const QByteArray& image, const QPoint& topLeft = QPoint());

private:
    QString m_name;
    QSize m_size;
    QScopedPointer<QPixmap> m_pixmap;
};
