#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtGui>
#include "canvas.h"
#include "brushengine.h"
#include "widgets/inputdevices.h"
#include "widgets/brushsettings.h"
#include "widgets/colorpicker.h"

const QString appName = "AprilBrush";
const QString appVersion = "0.0.1";

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow();

private slots:
    void createNewTabSlot();
    void openImageSlot();
    void saveImageSlot();
    void saveAsImageSlot();
    void activeTabSlot(int index);
    void closeTabSlot(int index);
    void aboutWindowSlot();
    void inputDevicesWindowSlot();
    void brushSettingsWindowSlot();
    void colorWindowSlot();
    void clearCanvasSlot();
    void changeColorSlot();

private:
    void createMenus();
    void createDockWindows();
    void createTabWidget();


    //QPointer<TestInputDevice> testIDWindow;
    InputDevices *inputDevices;
    BrushSettings *brushSettings;
    BrushEngine *brushEngine;
    ColorPicker *colorPicker;

    QTabWidget *tabWidget;
    Canvas *canvas;
    QList<Canvas *> canvasList;
};

#endif // MAINWINDOW_H
