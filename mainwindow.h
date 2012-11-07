#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtGui>
#include "canvas.h"
#include "brushengine.h"
#include "widgets/inputdevices.h"
#include "widgets/brushsettings.h"

const QString appName = "AprilBrush";
const QString appVersion = "0.0.1";

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow();

private slots:
    void aboutWindow();
    void InputDevicesWindow();
    void brushSettingsWindow();
    void colorWindow();
    void newTab();
    void clearCanvasCommand();

private:
    void createMenus();
    void createTabBar();
    void createNewTab();

    //QPointer<TestInputDevice> testIDWindow;
    InputDevices *inputDevices;
    BrushSettings *brushSettings;
    BrushEngine *brush;

    QTabWidget *tabBar;
    Canvas *canvas;
};

#endif // MAINWINDOW_H
