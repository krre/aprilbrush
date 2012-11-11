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
    void aboutWindowSlot();
    void InputDevicesWindowSlot();
    void brushSettingsWindowSlot();
    void colorWindowSlot();
    void clearCanvasSlot();

private:
    void createMenus();
    void createTabWidget();
    void createNewTab();

    //QPointer<TestInputDevice> testIDWindow;
    InputDevices *inputDevices;
    BrushSettings *brushSettings;
    BrushEngine *brushEngine;

    QTabWidget *tabWidget;
    Canvas *canvas;
};

#endif // MAINWINDOW_H
