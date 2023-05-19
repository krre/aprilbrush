#include "CanvasTabWidget.h"
#include "Canvas.h"
#include "core/Utils.h"
#include "engine/BrushEngine.h"
#include <QtWidgets>

CanvasTabWidget::CanvasTabWidget(QUndoGroup* undoGroup) : m_undoGroup(undoGroup) {
    setTabsClosable(true);
    connect(this, &QTabWidget::tabCloseRequested, this, &CanvasTabWidget::closeByIndex);
    connect(this, &QTabWidget::currentChanged, this, &CanvasTabWidget::onCurrentChanged);
}

Canvas* CanvasTabWidget::addCanvas(BrushEngine* brushEngine, EventFilter* eventFilter) {
    return addCanvas(nextName(), Utils::defaultCanvasSize(), brushEngine, eventFilter);
}

Canvas* CanvasTabWidget::addCanvas(const QString& name, const QSize& size, BrushEngine* brushEngine, EventFilter* eventFilter) {
    Canvas* canvas = new Canvas(size, brushEngine, eventFilter);
    canvas->setName(name);
    canvas->setFocus();
    connect(canvas, &Canvas::colorPicked, brushEngine, &BrushEngine::setColor);

    addTab(canvas, name);
    setCurrentIndex(count() - 1);

    m_undoGroup->addStack(canvas->undoStack());
    emit countChanged(count());
    return canvas;
}

QString CanvasTabWidget::nextName() {
    return tr("Untitled-%1").arg(m_maxTabCount++);
}

void CanvasTabWidget::closeByIndex(int index) {
    if (index < 0) return;

    Canvas* canvas = static_cast<Canvas*>(widget(index));
    m_undoGroup->removeStack(canvas->undoStack());

    removeTab(index);
    delete canvas;

    emit countChanged(count());
}

void CanvasTabWidget::closeCurrent() {
    closeByIndex(currentIndex());
}

void CanvasTabWidget::closeAll() {
    for (int i = count() - 1; i >= 0; i--) {
        closeByIndex(i);
    }
}

void CanvasTabWidget::closeOthers() {
    for (int i = count() - 1; i >= 0; i--) {
        if (widget(i) != currentWidget()) {
            closeByIndex(i);
        }
    }
}

void CanvasTabWidget::onCurrentChanged(int index) {
    if (index < 0) return;

    Canvas* canvas = static_cast<Canvas*>(widget(index));
    connect(canvas, &Canvas::inputDeviceDataChanged, this, &CanvasTabWidget::inputDeviceDataChanged);
    m_undoGroup->setActiveStack(canvas->undoStack());
}
