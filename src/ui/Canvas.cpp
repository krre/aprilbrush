#include "Canvas.h"
#include <QtGui>

Canvas::Canvas(const QSize& size) {
    qDebug() << size;
    resize(size);
}

void Canvas::mouseMoveEvent(QMouseEvent* event) {
    qDebug() << event->localPos();
}
