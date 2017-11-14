#include "CanvasItem.h"
#include <QtGui>

CanvasItem::CanvasItem() {
//    setRenderTarget(QQuickPaintedItem::FramebufferObject);
}

CanvasItem::~CanvasItem() {

}

void CanvasItem::paint(QPainter* painter) {
    painter->drawPixmap(0, 0, *_pixmap);
}

void CanvasItem::clear() {
    _pixmap->fill(Qt::transparent);
    update();
}

void CanvasItem::drawImage(const QByteArray& image) {
    QPixmap pixmap;
    pixmap.loadFromData(image);
    QPainter painter(_pixmap.data());
    painter.drawPixmap(0, 0, pixmap);
    update();
}

QByteArray CanvasItem::image(QPoint topleft, QPoint bottomright) {
    QByteArray ba;
    QBuffer buffer(&ba);
    buffer.open(QIODevice::WriteOnly);
    if (topleft.isNull()) {
        _pixmap->save(&buffer, "TIFF");
    } else {
        _pixmap->copy(QRect(topleft, bottomright)).save(&buffer, "TIFF");
    }
    buffer.close();
    return ba;
}

void CanvasItem::setImage(const QByteArray& image, QPoint topleft) {
    if (topleft.isNull()) {
        _pixmap->loadFromData(image);
    } else {
        QPixmap pixmap;
        pixmap.loadFromData(image);

        QPainter painter(_pixmap.data());
        painter.setCompositionMode(QPainter::CompositionMode_Source);
        painter.fillRect(QRect(topleft, pixmap.size()), Qt::transparent);
        painter.setCompositionMode(QPainter::CompositionMode_SourceOver);
        painter.drawPixmap(topleft, pixmap);
    }
    update();
}

void CanvasItem::setSize(QSize size) {
    if (_size == size) return;
    _size = size;
    if (size.width() && size.height()) {
        _pixmap.reset(new QPixmap(size));
        _pixmap->fill(Qt::transparent);
    }

    emit sizeChanged(size);
}
