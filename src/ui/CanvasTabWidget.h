#pragma once
#include <QTabWidget>

class CanvasTabWidget : public QTabWidget {
    Q_OBJECT
public:
    CanvasTabWidget();
    void addCanvas(const QSize& size = QSize());

private slots:
    void closeTab(int index);

private:
    int m_maxTabCount = 1;
};
