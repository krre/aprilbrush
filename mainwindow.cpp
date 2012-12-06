#include "mainwindow.h"

MainWindow::MainWindow()
{
    setWindowTitle(appName);
    resize(1100, 700);
    setWindowIcon(QIcon(":/icons/Butterfly_128x128.png"));
    createMenus();
    createTabWidget();
    brushEngine = new BrushEngine();    
    createNewTabSlot();
    brushSettings = new BrushSettings(brushEngine);
    inputDevices = new InputDevices(canvas);
    colorPicker = new ColorPicker(QColor(0, 0, 0));
    connect(colorPicker, SIGNAL(colorSignal()), this, SLOT(changeColorSlot()));
    createDockWindows();
}

void MainWindow::createMenus()
{
    QMenu *fileMenu = menuBar()->addMenu(tr("File"));
    fileMenu->addAction(tr("New"), this, SLOT(createNewTabSlot()), Qt::CTRL + Qt::Key_N);
    fileMenu->addAction(tr("Open"), this, SLOT(openImageSlot()), Qt::CTRL + Qt::Key_O);
    fileMenu->addAction(tr("Save"), this, SLOT(saveImageSlot()), Qt::CTRL + Qt::Key_S);
    fileMenu->addAction(tr("Save As..."), this, SLOT(saveAsImageSlot()), Qt::CTRL + Qt::SHIFT + Qt::Key_S);
    fileMenu->addSeparator();
    fileMenu->addAction(tr("Exit"), qApp, SLOT(quit()), Qt::CTRL + Qt::Key_Q);

    QMenu *editMenu = menuBar()->addMenu(tr("Edit"));
    editMenu->addAction(tr("Clear"), this, SLOT(clearCanvasSlot()), Qt::Key_Delete);

    QMenu *brushesMenu = menuBar()->addMenu(tr("Brushes"));
    brushesMenu->addAction(tr("Brush Settings..."), this, SLOT(brushSettingsWindowSlot()));

    QMenu *windowMenu = menuBar()->addMenu(tr("Window"));
    windowMenu->addAction(tr("Color"), this, SLOT(colorWindowSlot()));
    windowMenu->addAction(tr("Input Devices"), this, SLOT(inputDevicesWindowSlot()));

    QMenu *helpMenu = menuBar()->addMenu(tr("Help"));
    helpMenu->addAction(tr("About"), this, SLOT(aboutWindowSlot()));
    helpMenu->addAction(tr("About Qt"), qApp, SLOT(aboutQt()));
}

void MainWindow::createDockWindows()
{
    QWidget *widget = new QWidget;
    QBoxLayout *colorLayout = new QBoxLayout(QBoxLayout::TopToBottom);
    colorLayout->addWidget(colorPicker);
    colorLayout->addStretch();
    widget->setLayout(colorLayout);

    QDockWidget *dockColor = new QDockWidget(tr("Color"), this);
    dockColor->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);
    dockColor->setMaximumHeight(240); // temporary
    dockColor->setWidget(widget);
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
    connect(tabWidget, SIGNAL(tabCloseRequested(int)), this, SLOT(closeTabSlot(int)));
    connect(tabWidget, SIGNAL(currentChanged(int)), this, SLOT(activeTabSlot(int)));
}

void MainWindow::activeTabSlot(int index)
{
    canvas = canvasList.at(index);
}

void MainWindow::closeTabSlot(int index)
{
    canvasList.removeAt(index);
    tabWidget->removeTab(index);
    pathImageList.removeAt(index);
}

void MainWindow::createNewTabSlot()
{
    canvas = new Canvas(brushEngine);
    canvasList.append(canvas);
    pathImageList.append("");
    int index = tabWidget->count();
    QString tabName = tr("Untitled ") + QString::number(index + 1);
    tabWidget->addTab(canvas, tabName);
    tabWidget->setCurrentIndex(index);
}

void MainWindow::openImageSlot()
{
    QString filePath = QFileDialog::getOpenFileName(this, tr("Open image"), "C:/", tr("Images (*.png)"));
    if (!filePath.isEmpty())
    {
        createNewTabSlot();
        canvas->surface()->load(filePath);
        QFileInfo pathInfo(filePath);
        QString fileName(pathInfo.fileName());
        int index = tabWidget->currentIndex();
        tabWidget->setTabText(index, fileName);
        pathImageList.replace(index, filePath);
    }
}

void MainWindow::saveImageSlot()
{
    int index = tabWidget->currentIndex();
    QString savePath = pathImageList.at(index);
    if (!savePath.isEmpty())
        canvas->surface()->save(savePath);
    else
        saveAsImageSlot();
}

void MainWindow::saveAsImageSlot()
{
    QString filePath = QFileDialog::getSaveFileName(this, tr("Save image as"), "C:/", tr("Images (*.png)"));
    if (!filePath.isEmpty())
    {
        canvas->surface()->save(filePath);
        QFileInfo pathInfo(filePath);
        QString fileName(pathInfo.fileName());
        int index = tabWidget->currentIndex();
        tabWidget->setTabText(index, fileName);
        pathImageList.replace(index, filePath);
    }
}

void MainWindow::clearCanvasSlot()
{
    canvas->clearCanvasSlot();
}

void MainWindow::inputDevicesWindowSlot()
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



