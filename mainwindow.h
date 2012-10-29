#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtGui>
#include "canvas.h"
#include "widgets/testinputdevice.h"
#include "widgets/brushsettings.h"

const QString appName = "AprilBrush";
const QString appVersion = "0.0.1";

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow();

private slots:
    void aboutWindowAction();
    void testIDWindowAction();
    void brushSettingsWindowAction();
    void newTabAction();

private:
    void createActions();
    void createMenus();
    void createTabBar();
    void createNewTab(TestInputDevice *testIDWindow);

    // File
    QAction *newAction;
    QAction *openAction;
    QAction *saveAction;
    QAction *saveAsAction;
    QAction *exitAction;
    // Edit
    QAction *clearAction;
    // View
    QAction *testIDAction;
    // Brushes
    QAction *brushSettingsAction;
    // Help
    QAction *aboutAction;
    QAction *aboutQtAction;

    //QPointer<TestInputDevice> testIDWindow;
    TestInputDevice *testIDWindow;
    BrushSettings *brushSettingsWindow;

    QTabWidget *tabBar;
    Canvas *appCanvas;
};

#endif // MAINWINDOW_H
