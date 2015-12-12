#include "canvasitem.h"

CanvasItem::CanvasItem()
{
    setFlag(ItemHasContents, true);
    setAcceptedMouseButtons(Qt::AllButtons);
}

CanvasItem::~CanvasItem()
{
    delete m_image;
}

void CanvasItem::setSize(QSize size)
{
    if (m_size == size) return;

    m_size = size;
    m_image = new QImage(size, QImage::Format_RGBA8888);
    m_image->fill(Qt::gray);
    emit sizeChanged(size);
}

QSGNode* CanvasItem::updatePaintNode(QSGNode* node, QQuickItem::UpdatePaintNodeData*)
{
    QSGSimpleTextureNode* n = static_cast<QSGSimpleTextureNode*>(node);
    if (!n) {
        n = new QSGSimpleTextureNode();
        n->setOwnsTexture(true);
    }
    n->setTexture(window()->createTextureFromImage(*m_image));
    n->setRect(boundingRect());
    return n;
}

void CanvasItem::mouseMoveEvent(QMouseEvent* event)
{
    qDebug() << "move" << event;
}

void CanvasItem::mousePressEvent(QMouseEvent* event)
{
    qDebug() << "press" << event;
}

void CanvasItem::mouseReleaseEvent(QMouseEvent* event)
{
    qDebug() << "release" << event;
}

