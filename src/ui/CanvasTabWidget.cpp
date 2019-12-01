#include "CanvasTabWidget.h"
#include <QtWidgets>

CanvasTabWidget::CanvasTabWidget() {
    setTabsClosable(true);

    connect(this, &QTabWidget::tabCloseRequested, this, &CanvasTabWidget::closeTab);
}

void CanvasTabWidget::addCanvas(const QSize& size) {
    qDebug() << size;
    addTab(new QWidget, "Untitled");
}

void CanvasTabWidget::closeTab(int index) {
    QWidget* canvas = widget(index);
    removeTab(index);
    delete canvas;
}
