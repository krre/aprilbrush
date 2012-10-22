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
    void testID();

private:
    void createActions();
    void createMenus();
    void createTabBar();
    void createNewTab();

    QAction *newAction;
    QAction *openAction;
    QAction *saveAction;
    QAction *saveAsAction;
    QAction *exitAction;
    QAction *testIDAction;
    QAction *aboutAction;
    QAction *aboutQtAction;

    QTabWidget *tabBar;
    QPointer<QWidget> testIDWindow;
    Canvas *appCanvas;
};

#endif // MAINWINDOW_H
