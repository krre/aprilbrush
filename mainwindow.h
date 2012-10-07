#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

const QString appName = "AprilBrush";
const QString appVersion = "0.0.1";

class MainWindow : public QMainWindow
{
public:
    MainWindow(QWidget *parent=0);
};

#endif // MAINWINDOW_H
