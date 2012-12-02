#include "mainwindow.h"

MainWindow::MainWindow()
{
    setWindowTitle(appName);
    resize(1100, 700);
    setWindowIcon(QIcon(":/icons/Butterfly_128x128.png"));
    createMenus();
    createTabWidget();
    brushEngine = new BrushEngine();
    createNewTab();
    brushSettings = new BrushSettings(brushEngine);
    inputDevices = new InputDevices(canvas);
    colorPicker = new ColorPicker(QColor(0, 0, 0));
    connect(colorPicker, SIGNAL(colorSignal()), this, SLOT(changeColorSlot()));
    createDockWindows();
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
    editMenu->addAction(tr("Clear"), this, SLOT(clearCanvasSlot()), Qt::Key_Delete);

    QMenu *brushesMenu = menuBar()->addMenu(tr("Brushes"));
    brushesMenu->addAction(tr("Brush Settings..."), this, SLOT(brushSettingsWindowSlot()));

    QMenu *windowMenu = menuBar()->addMenu(tr("Window"));
    windowMenu->addAction(tr("Color"), this, SLOT(colorWindowSlot()));
    windowMenu->addAction(tr("Input Devices"), this, SLOT(InputDevicesWindowSlot()));

    QMenu *helpMenu = menuBar()->addMenu(tr("Help"));
    helpMenu->addAction(tr("About"), this, SLOT(aboutWindowSlot()));
    helpMenu->addAction(tr("About Qt"), qApp, SLOT(aboutQt()));
}

void MainWindow::createDockWindows()
{
    QDockWidget *dockColor = new QDockWidget(tr("Color"), this);
    dockColor->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);
    dockColor->setWidget(colorPicker);
    addDockWidget(Qt::RightDockWidgetArea, dockColor);

    QDockWidget *dockBrush = new QDockWidget(tr("Brush Settings"), this);
    dockBrush->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);
    dockBrush->setWidget(brushSettings);
    addDockWidget(Qt::RightDockWidgetArea, dockBrush);
}

void MainWindow::createTabWidget()
{
    tabWidget = new QTabWidget();
    tabWidget->setTabsClosable(true);
    setCentralWidget(tabWidget);
}

void MainWindow::createNewTab()
{
    canvas = new Canvas(brushEngine);
    tabWidget->addTab(canvas, "Untitled");
    tabWidget->setCurrentIndex(tabWidget->count() - 1);
}

void MainWindow::clearCanvasSlot()
{
    canvas->clearCanvasSlot();
}

void MainWindow::InputDevicesWindowSlot()
{
/*
    // Create the window if it doesn't exists
    if (!testIDWindow)
        testIDWindow = new TestInputDevice();
*/
    inputDevices->show();
}

void MainWindow::brushSettingsWindowSlot()
{
    brushSettings->show();
}

void MainWindow::colorWindowSlot()
{
    QColor color;
    color = QColorDialog::getColor(Qt::green, this);
    brushEngine->setColor(color.red(), color.green(), color.blue());
    colorPicker->setColor(color);
}

void MainWindow::changeColorSlot()
{
    brushEngine->setColor(colorPicker->color().red(), colorPicker->color().green(), colorPicker->color().blue());
}

void MainWindow::aboutWindowSlot()
{
    QString aboutText = "<h3><b>" + appName + "</b></h3>" +
            tr("Version ") + appVersion +
            tr("<br>Copyright &copy; 2012, Vladimir Zarypov");
    QMessageBox::about(this, "About " + appName, aboutText);
}



