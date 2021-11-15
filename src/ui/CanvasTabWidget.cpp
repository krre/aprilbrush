#include "CanvasTabWidget.h"
#include "Canvas.h"
#include "core/Utils.h"
#include <QtWidgets>

CanvasTabWidget::CanvasTabWidget() {
    setTabsClosable(true);
    connect(this, &QTabWidget::tabCloseRequested, this, &CanvasTabWidget::closeCanvas);
}

void CanvasTabWidget::addCanvas() {
    addCanvas(nextName(), Utils::defaultCanvasSize());
}

void CanvasTabWidget::addCanvas(const QString& name, const QSize& size) {
    Canvas* canvas = new Canvas(size);
    canvas->setName(name);
    addTab(canvas, name);
    setCurrentIndex(count() - 1);
    canvas->setFocus();
    emit countChanged(count());
}

QString CanvasTabWidget::nextName() {
    return tr("Untitled-%1").arg(maxTabCount++);
}

void CanvasTabWidget::closeCanvas(int index) {
    QWidget* canvas = widget(index);
    removeTab(index);
    delete canvas;
    emit countChanged(count());
}
