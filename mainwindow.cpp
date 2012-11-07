#include "mainwindow.h"

MainWindow::MainWindow()
{
    setWindowTitle(appName);
    resize(1100, 700);
    setWindowIcon(QIcon(":/icons/Butterfly_128x128.png"));
    createMenus();
    brush = new BrushEngine;
    createTabBar();
    createNewTab();
    inputDevices = new InputDevices(canvas);
    brushSettings = new BrushSettings(brush);
}

void MainWindow::createMenus()
{
    QMenu *fileMenu = menuBar()->addMenu(tr("File"));
    fileMenu->addAction(tr("New"), this, SLOT(close()), Qt::CTRL + Qt::Key_N);
    fileMenu->addAction(tr("Open"), this, SLOT(close()), Qt::CTRL + Qt::Key_O);
    fileMenu->addAction(tr("Save"), this, SLOT(close()), Qt::CTRL + Qt::Key_S);
    fileMenu->addAction(tr("Save As..."), this, SLOT(close()), Qt::CTRL + Qt::SHIFT + Qt::Key_S);
    fileMenu->addSeparator();
    fileMenu->addAction(tr("Exit"), qApp, SLOT(quit()), Qt::CTRL + Qt::Key_Q);

    QMenu *editMenu = menuBar()->addMenu(tr("Edit"));
    editMenu->addAction(tr("Clear"), this, SLOT(clearCanvasCommand()), Qt::Key_Delete);

    QMenu *brushesMenu = menuBar()->addMenu(tr("Brushes"));
    brushesMenu->addAction(tr("Brush Settings..."), this, SLOT(brushSettingsWindow()));

    QMenu *windowMenu = menuBar()->addMenu(tr("Window"));
    windowMenu->addAction(tr("Color"), this, SLOT(colorWindow()));
    windowMenu->addAction(tr("Input Devices"), this, SLOT(InputDevicesWindow()));

    QMenu *helpMenu = menuBar()->addMenu(tr("Help"));
    helpMenu->addAction(tr("About"), this, SLOT(aboutWindow()));
    helpMenu->addAction(tr("About Qt"), qApp, SLOT(aboutQt()));
}

void MainWindow::createTabBar()
{
    tabBar = new QTabWidget();
    tabBar->setTabsClosable(true);
    setCentralWidget(tabBar);
}

void MainWindow::createNewTab()
{
    canvas = new Canvas(brush);
    tabBar->addTab(canvas, "Untitled");
    tabBar->setCurrentIndex(tabBar->count() - 1);
}

void MainWindow::newTab()
{
    createNewTab();
}

void MainWindow::clearCanvasCommand()
{
    canvas->clearCanvas();
}

void MainWindow::InputDevicesWindow()
{
/*
    // Create the window if it doesn't exists
    if (!testIDWindow)
        testIDWindow = new TestInputDevice();
*/
    inputDevices->show();
}

void MainWindow::brushSettingsWindow()
{
    brushSettings->show();
}

void MainWindow::colorWindow()
{
    QColor color;
    color = QColorDialog::getColor(Qt::green, this);
    brush->setColor(color.red(), color.green(), color.blue());
}

void MainWindow::aboutWindow()
{
    QString aboutText = "<h3><b>" + appName + "</b></h3>" +
            tr("Version ") + appVersion +
            tr("<br>Copyright &copy; 2012, Vladimir Zarypov");
    QMessageBox::about(this, "About " + appName, aboutText);
}



