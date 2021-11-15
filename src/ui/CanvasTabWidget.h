#pragma once
#include <QTabWidget>

class CanvasTabWidget : public QTabWidget {
    Q_OBJECT
public:
    CanvasTabWidget();

    void addCanvas();
    void addCanvas(const QString& name, const QSize& size);

    QString nextName();

public slots:
    void closeCanvas(int index);

signals:
    void countChanged(int count);

private:
    int maxTabCount = 1;
};
