#include "mainwindow.h"
#include "undocommands.h"

MainWindow::MainWindow()
{
    setWindowTitle(appName);
    int appWidth = qApp->desktop()->width() * 0.95;
    int appHeigth = qApp->desktop()->height() * 0.85;
    resize(appWidth, appHeigth);
    setWindowIcon(QIcon(":/icons/Butterfly_128x128.png"));

    undoGroup = new QUndoGroup(this);
    undoView = new QUndoView(undoGroup);

    createMenus();
    maxTabCount = 1;
    createTabWidget();
    brushEngine = new BrushEngine();    
    createNewTabSlot();
    brushSettings = new BrushSettings(brushEngine);
    inputDevices = new InputDevices(canvas);
    colorPicker = new ColorPicker(QColor(0, 0, 0));
    connect(colorPicker, SIGNAL(colorSignal()), this, SLOT(changeColorSlot()));
    layerManager = new LayerManager();
    createDockWindows();
    canvas->setFocus();
}

void MainWindow::createMenus()
{
    QMenu *fileMenu = menuBar()->addMenu(tr("File"));
    fileMenu->addAction(tr("New"), this, SLOT(createNewTabSlot()), Qt::CTRL + Qt::Key_N);
    fileMenu->addAction(tr("Open..."), this, SLOT(openImageSlot()), Qt::CTRL + Qt::Key_O);
    fileMenu->addAction(tr("Save"), this, SLOT(saveImageSlot()), Qt::CTRL + Qt::Key_S);
    fileMenu->addAction(tr("Save As..."), this, SLOT(saveAsImageSlot()), Qt::CTRL + Qt::SHIFT + Qt::Key_S);
    fileMenu->addSeparator();
    fileMenu->addAction(tr("Close"), this, SLOT(closeImageSlot()), Qt::CTRL + Qt::Key_W);
    fileMenu->addAction(tr("Close All"), this, SLOT(closeAllImagesSlot()), Qt::CTRL + Qt::SHIFT + Qt::Key_W);
    fileMenu->addAction(tr("Close Others"), this, SLOT(closeOthersSlot()), Qt::CTRL + Qt::ALT + Qt::Key_W);
    fileMenu->addSeparator();
    fileMenu->addAction(tr("Exit"), qApp, SLOT(quit()), Qt::CTRL + Qt::Key_Q);

    QMenu *editMenu = menuBar()->addMenu(tr("Edit"));

    undoAction = undoGroup->createUndoAction(this, tr("Undo"));
    undoAction->setShortcuts(QKeySequence::Undo);
    editMenu->addAction(undoAction);

    redoAction = undoGroup->createRedoAction(this, tr("Redo"));
    redoAction->setShortcuts(QKeySequence::Redo);
    editMenu->addAction(redoAction);

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

    QDockWidget *colorDock = new QDockWidget(tr("Color"), this);
    colorDock->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);
    //colorDock->setMaximumHeight(240); // temporary
    colorDock->setWidget(widget);
    addDockWidget(Qt::RightDockWidgetArea, colorDock);

    QDockWidget *brushDock = new QDockWidget(tr("Brush Settings"), this);
    brushDock->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);
    brushDock->setWidget(brushSettings);
    addDockWidget(Qt::RightDockWidgetArea, brushDock);

    QDockWidget *commandDock = new QDockWidget(tr("Command List"), this);
    commandDock->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);
    commandDock->setWidget(undoView);
    addDockWidget(Qt::RightDockWidgetArea, commandDock);

    QDockWidget *layerDock = new QDockWidget(tr("Layers"), this);
    layerDock->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);
    layerDock->setWidget(layerManager);
    addDockWidget(Qt::RightDockWidgetArea, layerDock);
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
    if (index == -1)
        return;
    canvas = canvasList.at(index);
    undoGroup->setActiveStack(canvas->undoStack());
}

void MainWindow::closeTabSlot(int index)
{
    activeTabSlot(index);
    undoGroup->removeStack(canvas->undoStack());

    Canvas *dropCanvas;
    dropCanvas = canvas;

    canvasList.removeAt(index);
    tabWidget->removeTab(index);

    delete dropCanvas;
}

void MainWindow::createNewTabSlot()
{
    canvas = new Canvas(brushEngine);
    connect(canvas, SIGNAL(startPaintSignal()), this, SLOT(paintUndoSlot()));
    canvasList.append(canvas);
    int index = tabWidget->count();

    QString tabName = tr("Untitled ") + QString("%1").arg(maxTabCount++, 2, 10, QChar('0'));
    canvas->setName(tabName);
    tabWidget->addTab(canvas, tabName);
    tabWidget->setCurrentIndex(index);

    undoGroup->addStack(canvas->undoStack());
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
        canvas->setPath(filePath);
        canvas->setName(fileName);
    }
}

void MainWindow::saveImageSlot()
{
    if (!canvas->path().isEmpty())
        canvas->surface()->save(canvas->path());
    else
        saveAsImageSlot();
}

void MainWindow::saveAsImageSlot()
{
    //qDebug() <<  "C:/" + canvas->name() + ".png";
    QString filePath = QFileDialog::getSaveFileName(this, tr("Save image as"),  "C:/", tr("Images (*.png)"));
    if (!filePath.isEmpty())
    {
        canvas->surface()->save(filePath);
        QFileInfo pathInfo(filePath);
        QString fileName(pathInfo.fileName());
        int index = tabWidget->currentIndex();
        tabWidget->setTabText(index, fileName);
        canvas->setPath(filePath);
        canvas->setName(fileName);
    }
}

void MainWindow::closeImageSlot()
{
    int index = tabWidget->currentIndex();
    closeTabSlot(index);
}

void MainWindow::closeAllImagesSlot()
{
    int numTabs = tabWidget->count();
    for (int index = 0; index < numTabs; index++)
    {
        closeTabSlot(0);
    }
}

void MainWindow::closeOthersSlot()
{
    int numTabs = tabWidget->count() - 1;
    QWidget *activeTab = tabWidget->currentWidget();
    for (int index = 0; index < numTabs; index++)
    {
        if (tabWidget->widget(0) != activeTab)
            closeTabSlot(0);
        else
            closeTabSlot(1);
    }
}

void MainWindow::clearCanvasSlot()
{
    QUndoCommand *clearCommand = new ClearCommand(canvas);
    canvas->undoStack()->push(clearCommand);
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

void MainWindow::paintUndoSlot()
{
    QUndoCommand *paintCommand = new PaintCommand(canvas);
    canvas->undoStack()->push(paintCommand);
}

void MainWindow::aboutWindowSlot()
{
    QString aboutText = "<h3><b>" + appName + "</b></h3>" +
            tr("Version ") + appVersion +
            tr("<br>Copyright &copy; 2012, Vladimir Zarypov");
    QMessageBox::about(this, "About " + appName, aboutText);
}

