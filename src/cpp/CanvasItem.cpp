#include "CanvasItem.h"
#include <QtGui>

namespace AprilBrush {

CanvasItem::CanvasItem() {
//    setRenderTarget(QQuickPaintedItem::FramebufferObject);
}

CanvasItem::~CanvasItem() {

}

void CanvasItem::paint(QPainter* painter) {
    painter->drawPixmap(0, 0, *pixmap);
}

void CanvasItem::clear() {
    pixmap->fill(Qt::transparent);
    update();
}

void CanvasItem::drawImage(const QByteArray& image) {
    QPixmap pixmap;
    pixmap.loadFromData(image);
    QPainter painter(this->pixmap.data());
    painter.drawPixmap(0, 0, pixmap);
    update();
}

QByteArray CanvasItem::getImage(QPoint topleft, QPoint bottomright) {
    QByteArray ba;
    QBuffer buffer(&ba);
    buffer.open(QIODevice::WriteOnly);
    if (topleft.isNull()) {
        pixmap->save(&buffer, "TIFF");
    } else {
        pixmap->copy(QRect(topleft, bottomright)).save(&buffer, "TIFF");
    }
    buffer.close();
    return ba;
}

void CanvasItem::setImage(const QByteArray& image, QPoint topleft) {
    if (topleft.isNull()) {
        this->pixmap->loadFromData(image);
    } else {
        QPixmap pixmap;
        pixmap.loadFromData(image);

        QPainter painter(this->pixmap.data());
        painter.setCompositionMode(QPainter::CompositionMode_Source);
        painter.fillRect(QRect(topleft, pixmap.size()), Qt::transparent);
        painter.setCompositionMode(QPainter::CompositionMode_SourceOver);
        painter.drawPixmap(topleft, pixmap);
    }
    update();
}

void CanvasItem::setSize(QSize size) {
    if (this->size == size) return;
    this->size = size;
    if (size.width() && size.height()) {
        pixmap.reset(new QPixmap(size));
        pixmap->fill(Qt::transparent);
    }

    emit sizeChanged(size);
}

} // AprilBrush
