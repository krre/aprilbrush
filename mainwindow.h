#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtGui>
#include "canvas.h"
#include "brushengine.h"
#include "widgets/inputdevices.h"
#include "widgets/brushsettings.h"
#include "widgets/colorpicker.h"
#include "widgets/layermanager.h"

const QString appName = "AprilBrush";
const QString appVersion = "0.0.1";

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow();

private slots:
    // File
    void createNewTabSlot();
    void openImageSlot();
    void saveImageSlot();
    void saveAsImageSlot();
    void closeImageSlot();
    void closeAllImagesSlot();
    void closeOthersSlot();
    // Edit
    void clearCanvasSlot();

    void activeTabSlot(int index);
    void closeTabSlot(int index);
    void aboutWindowSlot();
    void inputDevicesWindowSlot();
    void brushSettingsWindowSlot();
    void colorWindowSlot();

    void changeColorSlot();
    void paintUndoSlot();

private:
    void createMenus();
    void createDockWindows();
    void createTabWidget();

    QAction *undoAction;
    QAction *redoAction;

    QUndoGroup *undoGroup;
    QUndoStack *undoStack;
    QUndoView *undoView;
    //QPointer<TestInputDevice> testIDWindow;
    InputDevices *inputDevices;
    BrushSettings *brushSettings;
    BrushEngine *brushEngine;
    ColorPicker *colorPicker;
    LayerManager *layerManager;

    QTabWidget *tabWidget;
    Canvas *canvas;
    QList<Canvas*> canvasList;
    QList<QString> pathImageList;
    QList<QUndoStack*> undoStackList;
};

#endif // MAINWINDOW_H
