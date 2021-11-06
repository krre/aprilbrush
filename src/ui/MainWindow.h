#pragma once
#include <QMainWindow>

class CanvasTabWidget;

class MainWindow : public QMainWindow {
    Q_OBJECT
public:
    explicit MainWindow(QWidget* parent = nullptr);

protected:
    void closeEvent(QCloseEvent* event) override;

private slots:
    void createFile();
    void onAbout();
    void onOptions();
    void onInputDevice();

private:
    void readSettings();
    void writeSettings();

    void createActions();
    void createUi();
    void applyHotSettings();

    CanvasTabWidget* canvasTabWidget;
};
