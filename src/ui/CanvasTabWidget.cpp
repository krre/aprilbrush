#include "CanvasTabWidget.h"
#include "Canvas.h"
#include <QtWidgets>

CanvasTabWidget::CanvasTabWidget() {
    setTabsClosable(true);

    connect(this, &QTabWidget::tabCloseRequested, this, &CanvasTabWidget::closeTab);
}

void CanvasTabWidget::addCanvas(const QSize& size) {
    QString tabName = tr("Untitled-%1").arg(m_maxTabCount++);
    addTab(new Canvas(size), tabName);
}

void CanvasTabWidget::closeTab(int index) {
    QWidget* canvas = widget(index);
    removeTab(index);
    delete canvas;
}
