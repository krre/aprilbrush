#include "Canvas.h"
#include "engine/BrushEngine.h"
#include "engine/Layer.h"
#include <QtGui>

Canvas::Canvas(const QSize& size) {
    resize(size);
    brushEngine.reset(new BrushEngine);
    addLayer(nextName());
}

Canvas::~Canvas() {

}

void Canvas::addLayer(const QString& name) {
    auto newLayer = QSharedPointer<Layer>(new Layer(name, size()));
    layers.append(newLayer);
    m_currentLayerIndex = layers.count() - 1;
    brushEngine->setLayer(currentLayer());
}

void Canvas::addLayer(const QSharedPointer<Layer>& layer) {

}

void Canvas::setCurrentLayerIndex(int index) {
    m_currentLayerIndex = index;
}

int Canvas::currentLayerIndex() const {
    return m_currentLayerIndex;
}

Layer* Canvas::currentLayer() const {
    return m_currentLayerIndex >= 0 ? layers.at(m_currentLayerIndex).data() : nullptr;
}

QString Canvas::nextName() {
    return tr("Untitled-%1").arg(maxTabCount++);
}

void Canvas::mouseMoveEvent(QMouseEvent* event) {
    brushEngine->paint(event->position());
    update();
}

void Canvas::paintEvent(QPaintEvent* event) {
    Q_UNUSED(event)
    QPainter painter(this);

    for (int i = layers.count() - 1; i >=0; i--) {
        painter.drawPixmap(0, 0, *layers.at(i)->pixmap());
    }
}
