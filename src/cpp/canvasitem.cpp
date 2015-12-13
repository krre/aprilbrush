#include "canvasitem.h"
#include "tableteventfilter.h"

extern QPointer<TabletEventFilter> tabletEventFilter;

CanvasItem::CanvasItem()
{
    setFlag(ItemHasContents, true);
    setAcceptedMouseButtons(Qt::AllButtons);
}

CanvasItem::~CanvasItem()
{
    delete m_pixmap;
}

void CanvasItem::clear()
{
    m_pixmap->fill(Qt::transparent);
    update();
}

void CanvasItem::setSize(QSize size)
{
    if (m_size == size) return;

    m_size = size;
    m_pixmap = new QPixmap(size);
    m_pixmap->fill(Qt::transparent);
    emit sizeChanged(size);
}

QSGNode* CanvasItem::updatePaintNode(QSGNode* node, QQuickItem::UpdatePaintNodeData*)
{
    QSGSimpleTextureNode* n = static_cast<QSGSimpleTextureNode*>(node);
    if (!n) {
        n = new QSGSimpleTextureNode();
        n->setOwnsTexture(true);
        n->setRect(m_pixmap->rect());
    }
    n->setTexture(window()->createTextureFromImage(m_pixmap->toImage()));
    return n;
}
