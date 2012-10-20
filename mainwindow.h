#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
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

    QAction *exitAction;
    QAction *testIDAction;
    QAction *aboutAction;
    QAction *aboutQtAction;

    QPointer<QWidget> testIDWindow;
};

#endif // MAINWINDOW_H
