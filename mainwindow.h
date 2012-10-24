#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtGui>
#include "canvas.h"
#include "widgets/testinputdevice.h"

const QString appName = "AprilBrush";
const QString appVersion = "0.0.1";

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow();

private slots:
    void about();
    void testIDWindowAction();
    void newTabAction();

private:
    void createActions();
    void createMenus();
    void createTabBar();
    void createNewTab(TestInputDevice *testIDWindow);

    QAction *newAction;
    QAction *openAction;
    QAction *saveAction;
    QAction *saveAsAction;
    QAction *exitAction;
    QAction *testIDAction;
    QAction *aboutAction;
    QAction *aboutQtAction;

    //QPointer<TestInputDevice> testIDWindow;
    TestInputDevice *testIDWindow;
    QTabWidget *tabBar;
    Canvas *appCanvas;
};

#endif // MAINWINDOW_H
