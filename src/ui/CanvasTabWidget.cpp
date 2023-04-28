#include "CanvasTabWidget.h"
#include "Canvas.h"
#include "core/Utils.h"
#include <QtWidgets>

CanvasTabWidget::CanvasTabWidget(QUndoGroup* undoGroup) : undoGroup(undoGroup) {
    setTabsClosable(true);
    connect(this, &QTabWidget::tabCloseRequested, this, &CanvasTabWidget::closeCanvas);
    connect(this, &QTabWidget::currentChanged, this, &CanvasTabWidget::onCurrentChanged);
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
    undoGroup->addStack(canvas->undoStack());
    emit countChanged(count());
}

QString CanvasTabWidget::nextName() {
    return tr("Untitled-%1").arg(maxTabCount++);
}

void CanvasTabWidget::closeCanvas(int index) {
    Canvas* canvas = static_cast<Canvas*>(widget(index));
    removeTab(index);
    undoGroup->removeStack(canvas->undoStack());
    delete canvas;
    emit countChanged(count());
}

void CanvasTabWidget::onCurrentChanged(int index) {
    if (index >= 0) {
        Canvas* canvas = static_cast<Canvas*>(widget(index));
        undoGroup->setActiveStack(canvas->undoStack());
    }
}
