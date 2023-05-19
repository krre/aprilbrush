#include "CanvasTabWidget.h"
#include "Canvas.h"
#include "core/Utils.h"
#include "engine/BrushEngine.h"
#include <QtWidgets>

CanvasTabWidget::CanvasTabWidget(QUndoGroup* undoGroup) : m_undoGroup(undoGroup) {
    setTabsClosable(true);
    connect(this, &QTabWidget::tabCloseRequested, this, &CanvasTabWidget::closeCanvas);
    connect(this, &QTabWidget::currentChanged, this, &CanvasTabWidget::onCurrentChanged);
}

void CanvasTabWidget::addCanvas(BrushEngine* brushEngine, EventFilter* eventFilter) {
    addCanvas(nextName(), Utils::defaultCanvasSize(), brushEngine, eventFilter);
}

void CanvasTabWidget::addCanvas(const QString& name, const QSize& size, BrushEngine* brushEngine, EventFilter* eventFilter) {
    Canvas* canvas = new Canvas(size, brushEngine, eventFilter);
    connect(canvas, &Canvas::colorPicked, brushEngine, &BrushEngine::setColor);

    canvas->setName(name);
    addTab(canvas, name);
    setCurrentIndex(count() - 1);
    canvas->setFocus();
    m_undoGroup->addStack(canvas->undoStack());
    emit countChanged(count());
}

QString CanvasTabWidget::nextName() {
    return tr("Untitled-%1").arg(m_maxTabCount++);
}

void CanvasTabWidget::closeCanvas(int index) {
    if (index < 0) return;

    Canvas* canvas = static_cast<Canvas*>(widget(index));
    m_undoGroup->removeStack(canvas->undoStack());

    removeTab(index);
    delete canvas;

    emit countChanged(count());
}

void CanvasTabWidget::onCurrentChanged(int index) {
    if (index < 0) return;

    Canvas* canvas = static_cast<Canvas*>(widget(index));
    connect(canvas, &Canvas::inputDeviceDataChanged, this, &CanvasTabWidget::inputDeviceDataChanged);
    m_undoGroup->setActiveStack(canvas->undoStack());
}
