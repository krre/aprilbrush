#pragma once
#include <QTabWidget>

class CanvasTabWidget : public QTabWidget {
    Q_OBJECT
public:
    CanvasTabWidget();
    void addCanvas(const QSize& size);

private slots:
    void closeTab(int index);
};
