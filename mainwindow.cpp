#include "mainwindow.h"
#include "canvas.h"
#include "widgets/testinputdevice.h"

MainWindow::MainWindow()
{
    setWindowTitle(appName);
    resize(1100, 700);
    setWindowIcon(QIcon(":/icons/Butterfly_128x128.png"));

    createActions();
    createMenus();
    createTabBar();
    testIDWindow = new TestInputDevice(); // for testing
    brushSettingsWindow = new BrushSettings;
    createNewTab(testIDWindow);
}

void MainWindow::createActions()
{
    newAction = new QAction(tr("New"), this);
    //connect(newAction, SIGNAL(triggered()), this, SLOT(close()));

    openAction = new QAction(tr("Open"), this);
    //connect(openAction, SIGNAL(triggered()), this, SLOT(close()));

    saveAction = new QAction(tr("Save"), this);
    //connect(saveAction, SIGNAL(triggered()), this, SLOT(close()));

    saveAsAction = new QAction(tr("Save As..."), this);
    //connect(saveAsAction, SIGNAL(triggered()), this, SLOT(close()));

    exitAction = new QAction(tr("Exit"), this);
    connect(exitAction, SIGNAL(triggered()), this, SLOT(close()));

    clearAction = new QAction(tr("Clear"), this);
    //connect(clearAction, SIGNAL(triggered()), appCanvas, SLOT(clearAction()));

    testIDAction = new QAction(tr("Test Input Devices..."), this);
    connect(testIDAction, SIGNAL(triggered()), this, SLOT(testIDWindowAction()));

    brushSettingsAction = new QAction(tr("Brushes Settings..."), this);
    connect(brushSettingsAction, SIGNAL(triggered()), this, SLOT(brushSettingsWindowAction()));

    aboutAction = new QAction(tr("About"), this);
    connect(aboutAction, SIGNAL(triggered()), this, SLOT(aboutWindowAction()));

    aboutQtAction = new QAction(tr("About Qt"), this);
    connect(aboutQtAction, SIGNAL(triggered()), qApp, SLOT(aboutQt()));
}

void MainWindow::createMenus()
{
    QMenu *fileMenu = menuBar()->addMenu(tr("File"));
    fileMenu->addAction(newAction);
    fileMenu->addAction(openAction);
    fileMenu->addAction(saveAction);
    fileMenu->addAction(saveAsAction);
    fileMenu->addSeparator();
    fileMenu->addAction(exitAction);

    QMenu *editMenu = menuBar()->addMenu(tr("Edit"));
    editMenu->addAction(clearAction);

    QMenu *viewMenu = menuBar()->addMenu(tr("View"));
    viewMenu->addAction(testIDAction);

    QMenu *brushesMenu = menuBar()->addMenu(tr("Brushes"));
    brushesMenu->addAction(brushSettingsAction);

    QMenu *helpMenu = menuBar()->addMenu(tr("Help"));
    helpMenu->addAction(aboutAction);
    helpMenu->addAction(aboutQtAction);
}

void MainWindow::createTabBar()
{
    tabBar = new QTabWidget();
    tabBar->setTabsClosable(true);
    setCentralWidget(tabBar);
}

void MainWindow::createNewTab(TestInputDevice *testIDWindow)
{
    Canvas *appCanvas = new Canvas(testIDWindow);
    tabBar->addTab(appCanvas, "Untitled");
    tabBar->setCurrentIndex(tabBar->count() - 1);
    connect(clearAction, SIGNAL(triggered()), appCanvas, SLOT(clearAction()));
}

void MainWindow::newTabAction()
{
    createNewTab(testIDWindow);
}

void MainWindow::testIDWindowAction()
{
/*
    // Create the window if it doesn't exists
    if (!testIDWindow)
        testIDWindow = new TestInputDevice();
*/
    testIDWindow->show();
}

void MainWindow::brushSettingsWindowAction()
{
    brushSettingsWindow->show();
}

void MainWindow::aboutWindowAction()
{
    QString aboutText = "<h3><b>" + appName + "</b></h3>" +
            tr("Version ") + appVersion +
            tr("<br>Copyright &copy; 2012, Vladimir Zarypov");
    QMessageBox::about(this, "About " + appName, aboutText);
}



