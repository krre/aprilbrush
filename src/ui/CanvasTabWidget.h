#pragma once
#include <QTabWidget>

class MainWindow;

class CanvasTabWidget : public QTabWidget {
    Q_OBJECT
public:
    CanvasTabWidget(MainWindow* mainWindow);

    void addCanvas();
    void addCanvas(const QString& name, const QSize& size);

    QString nextName();

public slots:
    void closeCanvas(int index);

signals:
    void countChanged(int count);

private slots:
    void onCurrentChanged(int index);

private:
    int maxTabCount = 1;
    MainWindow* mainWindow;
};
