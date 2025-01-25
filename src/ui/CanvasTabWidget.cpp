#include "CanvasTabWidget.h"
#include "Canvas.h"
#include "engine/BrushEngine.h"
#include <QUndoGroup>

CanvasTabWidget::CanvasTabWidget(BrushEngine* brushEngine, QUndoGroup* undoGroup)
    : m_brushEngine(brushEngine), m_undoGroup(undoGroup) {
    setTabsClosable(true);
    connect(this, &QTabWidget::tabCloseRequested, this, &CanvasTabWidget::closeByIndex);
    connect(this, &QTabWidget::currentChanged, this, &CanvasTabWidget::onCurrentChanged);
}

Canvas* CanvasTabWidget::addCanvas() {
    return addCanvas(nextName(), Canvas::defaultSize());
}

Canvas* CanvasTabWidget::addCanvas(const QString& name, const QSize& size) {
    Canvas* canvas = new Canvas(size, m_brushEngine);
    canvas->setName(name);
    canvas->setFocus();
    connect(canvas, &Canvas::colorPicked, m_brushEngine, &BrushEngine::setColor);

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
