#include "Layer.h"
#include <QtGui>

Layer::Layer(const QString& name, const QSize& size) {
    setName(name);
    setSize(size);
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
        m_pixmap = QPixmap(size);
        m_pixmap.fill(Qt::transparent);
    }
}

void Layer::clear() {
    m_pixmap.fill(Qt::transparent);
}

QByteArray Layer::image(const QPoint& topLeft, const QPoint& bottomRight) {
    QByteArray result;
    QBuffer buffer(&result);
    buffer.open(QIODevice::WriteOnly);

    if (topLeft.isNull()) {
        m_pixmap.save(&buffer, "TIFF");
    } else {
        m_pixmap.copy(QRect(topLeft, bottomRight)).save(&buffer, "TIFF");
    }

    buffer.close();
    return result;
}

void Layer::setImage(const QByteArray& image, const QPoint& topLeft) {
    if (topLeft.isNull()) {
        m_pixmap.loadFromData(image);
    } else {
        QPixmap pixmap;
        pixmap.loadFromData(image);

        QPainter painter(&m_pixmap);
        painter.setCompositionMode(QPainter::CompositionMode_Source);
        painter.fillRect(QRect(topLeft, pixmap.size()), Qt::transparent);
        painter.setCompositionMode(QPainter::CompositionMode_SourceOver);
        painter.drawPixmap(topLeft, pixmap);
    }
}

void Layer::setVisible(bool visible) {
    m_visible = visible;
}

bool Layer::isVisible() const {
    return m_visible;
}

void Layer::setLocked(bool locked) {
    m_locked = locked;
}

bool Layer::isLocked() const {
    return m_locked;
}

void Layer::setSelected(bool selected) {
    m_selected = selected;
}

bool Layer::isSelected() const {
    return m_selected;
}

QPixmap* Layer::pixmap() {
    return &m_pixmap;
}

void Layer::setPixmap(const QPixmap& pixmap) {
    m_pixmap = pixmap;
}

QByteArray Layer::data() const {
    QByteArray result;
    QBuffer buffer(&result);

    buffer.open(QIODevice::WriteOnly);
    m_pixmap.save(&buffer, "PNG");
    buffer.close();

    return result;
}

void Layer::setData(QByteArray& data) {
    m_pixmap.loadFromData(data, "PNG");
}
