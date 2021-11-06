#include "Canvas.h"
#include "engine/BrushEngine.h"
#include "engine/Layer.h"
#include <QtGui>

Canvas::Canvas(const QSize& size) {
    resize(size);
    brushEngine.reset(new BrushEngine);
}

Canvas::~Canvas() {

}

void Canvas::addLayer(const QString& name) {

}

void Canvas::addLayer(const QSharedPointer<Layer>& layer) {

}

void Canvas::mouseMoveEvent(QMouseEvent* event) {
    qDebug() << event->position();
    update();
}

void Canvas::paintEvent(QPaintEvent* event) {
    Q_UNUSED(event)
    QPainter painter(this);

    for (int i = layers.count() - 1; i >=0; i--) {
        painter.drawPixmap(0, 0, *layers.at(i)->pixmap());
    }
}
