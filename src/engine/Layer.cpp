#include "Layer.h"
#include <QtGui>

void Layer::paint(QPainter* painter) {
    painter->drawPixmap(0, 0, *m_pixmap);
}

const QSize& Layer::size() const {
    return m_size;
}

void Layer::clear() {
    m_pixmap->fill(Qt::transparent);
    update();
}

void Layer::drawImage(const QByteArray& image) {
    QPixmap pixmap;
    pixmap.loadFromData(image);
    QPainter painter(m_pixmap.data());
    painter.drawPixmap(0, 0, pixmap);
    update();
}

QByteArray Layer::image(QPoint topleft, QPoint bottomright) {
    QByteArray ba;
    QBuffer buffer(&ba);
    buffer.open(QIODevice::WriteOnly);

    if (topleft.isNull()) {
        m_pixmap->save(&buffer, "TIFF");
    } else {
        m_pixmap->copy(QRect(topleft, bottomright)).save(&buffer, "TIFF");
    }

    buffer.close();
    return ba;
}

void Layer::setImage(const QByteArray& image, QPoint topleft) {
    if (topleft.isNull()) {
        this->m_pixmap->loadFromData(image);
    } else {
        QPixmap pixmap;
        pixmap.loadFromData(image);

        QPainter painter(this->m_pixmap.data());
        painter.setCompositionMode(QPainter::CompositionMode_Source);
        painter.fillRect(QRect(topleft, pixmap.size()), Qt::transparent);
        painter.setCompositionMode(QPainter::CompositionMode_SourceOver);
        painter.drawPixmap(topleft, pixmap);
    }

    update();
}

void Layer::setSize(QSize size) {
    if (m_size == size) return;
    m_size = size;

    if (size.width() && size.height()) {
        m_pixmap.reset(new QPixmap(size));
        m_pixmap->fill(Qt::transparent);
    }

    emit sizeChanged(size);
}

QPixmap* Layer::pixmap() const {
    return m_pixmap.data();
}
