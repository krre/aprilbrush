#include "Layer.h"
#include <QtGui>

Layer::Layer(const QString& name, const QSize& size) {
    setName(name);

    if (size.isValid()) {
        m_pixmap = QPixmap(size);
        clear();
    }
}

void Layer::setName(const QString& name) {
    m_name = name;
}

const QString& Layer::name() const {
    return m_name;
}

QSize Layer::size() const {
    return m_pixmap.size();
}

void Layer::clear() {
    m_pixmap.fill(Qt::transparent);
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

void Layer::setData(const QByteArray& data) {
    m_pixmap.loadFromData(data, "PNG");
}
