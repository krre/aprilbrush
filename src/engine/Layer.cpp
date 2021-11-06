#include "Layer.h"
#include <QtGui>

Layer::Layer(const QString& name, const QSize& size) : m_name(name), m_size(size) {

}

Layer::~Layer() {

}

void Layer::setName(const QString& name) {
    m_name = name;
}

const QString& Layer::name() const {
    return m_name;
}

const QSize& Layer::size() const {
    return m_size;
}

void Layer::setSize(QSize size) {
    m_size = size;

    if (size.width() && size.height()) {
        m_pixmap.reset(new QPixmap(size));
        m_pixmap->fill(Qt::transparent);
    }
}

void Layer::clear() {
    m_pixmap->fill(Qt::transparent);
}

QByteArray Layer::image(const QPoint& topLeft, const QPoint& bottomRight) {
    QByteArray result;
    QBuffer buffer(&result);
    buffer.open(QIODevice::WriteOnly);

    if (topLeft.isNull()) {
        m_pixmap->save(&buffer, "TIFF");
    } else {
        m_pixmap->copy(QRect(topLeft, bottomRight)).save(&buffer, "TIFF");
    }

    buffer.close();
    return result;
}

void Layer::setImage(const QByteArray& image, const QPoint& topLeft) {
    if (topLeft.isNull()) {
        m_pixmap->loadFromData(image);
    } else {
        QPixmap pixmap;
        pixmap.loadFromData(image);

        QPainter painter(m_pixmap.data());
        painter.setCompositionMode(QPainter::CompositionMode_Source);
        painter.fillRect(QRect(topLeft, pixmap.size()), Qt::transparent);
        painter.setCompositionMode(QPainter::CompositionMode_SourceOver);
        painter.drawPixmap(topLeft, pixmap);
    }
}

QPixmap* Layer::pixmap() const {
    return m_pixmap.data();
}
