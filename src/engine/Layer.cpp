#include "Layer.h"
#include <QtGui>

Layer::Layer(const QString& name, const QSize& size) {
    setName(name);

    if (size.isValid()) {
        m_pixmap.reset(new QPixmap(size));
        clear();
    }
}

Layer::Layer(const QString& name, const QPixmap& pixmap) {
    setName(name);
    setPixmap(pixmap);
}

Layer::Layer(const Layer& layer) {
    m_pixmap.reset(new QPixmap(*layer.m_pixmap.data()));
}

Layer& Layer::operator=(const Layer& layer) {
    if (this == &layer) return *this;

    m_pixmap.reset(new QPixmap(*layer.m_pixmap));
    return *this;
}

Layer::~Layer() {

}

void Layer::setName(const QString& name) {
    m_name = name;
}

QString Layer::name() const {
    return m_name;
}

QSize Layer::size() const {
    return m_pixmap->size();
}

void Layer::clear() {
    m_pixmap->fill(Qt::transparent);
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

QPixmap* Layer::pixmap() const {
    return m_pixmap.data();
}

void Layer::setPixmap(const QPixmap& pixmap) {
    m_pixmap.reset(new QPixmap(pixmap));
}
