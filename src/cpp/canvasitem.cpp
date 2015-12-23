#include "canvasitem.h"

CanvasItem::CanvasItem()
{
//    setRenderTarget(QQuickPaintedItem::FramebufferObject);
}

CanvasItem::~CanvasItem()
{
    delete m_pixmap;
}

void CanvasItem::paint(QPainter* painter)
{
    painter->drawPixmap(0, 0, *m_pixmap);
}

void CanvasItem::clear()
{
    m_pixmap->fill(Qt::transparent);
    update();
}

void CanvasItem::drawBase64Image(const QString& image)
{
    QPainter painter(m_pixmap);
    QByteArray ba = QByteArray::fromBase64(image.toLatin1());
    QPixmap pixmap(m_pixmap->width(), m_pixmap->height());
    pixmap.loadFromData(ba);
    painter.drawPixmap(0, 0, pixmap);
    update();
}

void CanvasItem::setBase64Image(const QString& image)
{
    QByteArray ba = QByteArray::fromBase64(image.toLatin1());
    m_pixmap->fill(Qt::transparent);
    m_pixmap->loadFromData(ba);
    update();
}

QByteArray CanvasItem::image(QPoint topleft, QPoint bottomright)
{
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

void CanvasItem::setImage(const QByteArray& image, QPoint topleft)
{
    if (topleft.isNull()) {
        m_pixmap->loadFromData(image);
    } else {
        QPixmap pixmap;
        pixmap.loadFromData(image);

        QPainter painter(m_pixmap);
        painter.setCompositionMode(QPainter::CompositionMode_Source);
        painter.fillRect(QRect(topleft, pixmap.size()), Qt::transparent);
        painter.setCompositionMode(QPainter::CompositionMode_SourceOver);
        painter.drawPixmap(topleft, pixmap);
    }
    update();
}

QByteArray CanvasItem::byteArray()
{
    QByteArray ba;
    QBuffer buffer(&ba);
    buffer.open(QIODevice::WriteOnly);
    m_pixmap->save(&buffer, "PNG");
    buffer.close();
    return ba;
}

void CanvasItem::setByteArray(const QByteArray& ba)
{
    m_pixmap->loadFromData(ba, "PNG");
    update();
}

void CanvasItem::setSize(QSize size)
{
    if (m_size == size) return;
    m_size = size;
    if (size.width() && size.height()) {
        m_pixmap = new QPixmap(size);
        m_pixmap->fill(Qt::transparent);
    }

    emit sizeChanged(size);
}
