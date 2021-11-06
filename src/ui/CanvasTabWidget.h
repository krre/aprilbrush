#pragma once
#include <QTabWidget>

class CanvasTabWidget : public QTabWidget {
    Q_OBJECT
public:
    CanvasTabWidget();

    void addCanvas();
    void addCanvas(const QString& name, const QSize& size);

    QString nextName();

private slots:
    void closeCanvas(int index);

private:
    int maxTabCount = 1;
};
