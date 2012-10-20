#include "mainwindow.h"
#include "widgets/testinputdevice.h"

MainWindow::MainWindow()
{
    setWindowTitle(appName);
    resize(1100, 700);

    createActions();
    createMenus();
}

void MainWindow::createActions()
{
    exitAction = new QAction("Exit", this);
    connect(exitAction, SIGNAL(triggered()), this, SLOT(close()));

    testIDAction = new QAction("Test Input Devices", this);
    connect(testIDAction, SIGNAL(triggered()), this, SLOT(testID()));

    aboutAction = new QAction("About", this);
    connect(aboutAction, SIGNAL(triggered()), this, SLOT(about()));

    aboutQtAction = new QAction("About Qt", this);
    connect(aboutQtAction, SIGNAL(triggered()), qApp, SLOT(aboutQt()));
}

void MainWindow::createMenus()
{
    QMenu *fileMenu = menuBar()->addMenu("File");
    fileMenu->addAction(exitAction);

    QMenu *viewMenu = menuBar()->addMenu("View");
    viewMenu->addAction(testIDAction);

    QMenu *helpMenu = menuBar()->addMenu("Help");
    helpMenu->addAction(aboutAction);
    helpMenu->addAction(aboutQtAction);
}

void MainWindow::testID()
{
    TestInputDevice *testIDWindow = new TestInputDevice();
    testIDWindow->show();
}

void MainWindow::about()
{
    QString aboutText = appName + "\n" +
            "Version " + appVersion + "\n" +
            "Copyright (c) 2012, Vladimir Zarypov";
    QMessageBox::about(this, "About " + appName, aboutText);
}
