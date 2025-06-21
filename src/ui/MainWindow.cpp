#include "MainWindow.h"
#include "CanvasTabWidget.h"
#include "NewImage.h"
#include "Preferences.h"
#include "Canvas.h"
#include "InputDevice.h"
#include "ColorPicker.h"
#include "BrushSettings.h"
#include "core/Application.h"
#include "settings/FileSettings.h"
#include "engine/BrushEngine.h"
#include <QFileDialog>
#include <QMenuBar>
#include <QMessageBox>
#include <QDockWidget>
#include <QUndoGroup>
#include <QUndoView>
#include <QCloseEvent>

MainWindow::MainWindow() {
    m_fileSettings.reset(new FileSettings);

    m_undoGroup = new QUndoGroup(this);
    m_brushEngine = new BrushEngine(this);
    m_canvasTabWidget = new CanvasTabWidget(m_brushEngine, m_undoGroup);

    setCentralWidget(m_canvasTabWidget);

    createActions();
    createUi();
    readSettings();

    m_canvasTabWidget->addCanvas();
}

MainWindow::~MainWindow() {

}

void MainWindow::closeEvent(QCloseEvent* event) {
    writeSettings();
    event->accept();
}

void MainWindow::create() {
    NewImage newImage(m_canvasTabWidget->nextName(), m_fileSettings.data());

    if (newImage.exec() == QDialog::Accepted) {
        m_canvasTabWidget->addCanvas(newImage.name(), newImage.size());
    }
}

void MainWindow::open() {
    QString filePath = QFileDialog::getOpenFileName(this, tr("Open Image"), QString(), tr("Images (*.ora)"));

    if (!filePath.isEmpty()) {
        Canvas* canvas = m_canvasTabWidget->addCanvas();
        canvas->open(filePath);
        m_canvasTabWidget->setTabText(m_canvasTabWidget->currentIndex(), canvas->name());
    }
}

void MainWindow::save() {
    if (!currentCanvas()->filePath().isEmpty()) {
        currentCanvas()->save();
    } else {
        saveAs();
    }
}

void MainWindow::saveAs() {
    QString filePath = QFileDialog::getSaveFileName(this, tr("Save Image As"),  currentCanvas()->name() + ".ora", tr("OpenRaster (*.ora)"));

    if (!filePath.isEmpty()) {
        QString oraPath = filePath.last(4) != ".ora" ? filePath + ".ora" : filePath;
        currentCanvas()->setFilePath(oraPath);
        currentCanvas()->save();
        m_canvasTabWidget->setTabText(m_canvasTabWidget->currentIndex(), currentCanvas()->name());
    }
}

void MainWindow::exportImage() {
    QString fileName = currentCanvas()->name() + ".png";
    QString filePath = QFileDialog::getSaveFileName(this, tr("Export Image"), fileName, tr("Images (*.png)"));

    if (!filePath.isEmpty()) {
        currentCanvas()->exportPng(filePath);
    }
}

void MainWindow::clear() {
    currentCanvas()->clear();
}

void MainWindow::showAbout() {
    QMessageBox::about(this, tr("About %1").arg(Application::Name),
tr(R"(<h3>%1 %2</h3>
Painting application<br><br>
Based on Qt %3<br>
Build on %4 %5<br><br>
<a href=%6>%6</a><br><br>
Copyright © %7, Vladimir Zarypov)")
        .arg(Application::Name, Application::Version, QT_VERSION_STR, Application::BuildDate,
        Application::BuildTime, Application::Url, Application::Years));
}

void MainWindow::showPreferences() {
    Preferences preferences(m_fileSettings.data());

    if (preferences.exec() == QDialog::Accepted) {
        applyHotSettings();
    }
}

void MainWindow::showInputDevice() {
    auto inputDevice = new InputDevice(m_fileSettings.data(), this);
    connect(m_canvasTabWidget, &CanvasTabWidget::inputDeviceDataChanged, inputDevice, &InputDevice::setData);
    inputDevice->show();
}

void MainWindow::readSettings() {
    QByteArray geometry = m_fileSettings->mainWindowGeometry();

    if (!geometry.isEmpty()) {
        restoreGeometry(geometry);
    } else {
        const QRect availableGeometry = QGuiApplication::screens().constFirst()->availableGeometry();
        resize(availableGeometry.width() / 2, availableGeometry.height() / 2);
        move((availableGeometry.width() - width()) / 2, (availableGeometry.height() - height()) / 2);
    }

    restoreState(m_fileSettings->mainWindowState());
    m_colorPicker->setColor(m_fileSettings->colorPickerColor());
}

void MainWindow::writeSettings() {
    m_fileSettings->setMainWindowGeometry(saveGeometry());
    m_fileSettings->setMainWindowState(saveState());
    m_fileSettings->setColorPickerColor(m_colorPicker->color());
}

void MainWindow::createActions() {
    // File
    QMenu* fileMenu = menuBar()->addMenu(tr("File"));
    fileMenu->addAction(tr("New..."), Qt::CTRL | Qt::Key_N, this, &MainWindow::create);
    fileMenu->addAction(tr("Open..."), Qt::CTRL | Qt::Key_O, this, &MainWindow::open);

    QAction* saveAction = fileMenu->addAction(tr("Save"), Qt::CTRL | Qt::Key_S, this, &MainWindow::save);
    QAction* saveAsAction = fileMenu->addAction(tr("Save As..."), Qt::CTRL | Qt::SHIFT | Qt::Key_S, this, &MainWindow::saveAs);
    QAction* exportAction = fileMenu->addAction(tr("Export..."), Qt::CTRL | Qt::Key_E, this, &MainWindow::exportImage);
    fileMenu->addSeparator();

    QAction* closeAction = fileMenu->addAction(tr("Close"), Qt::CTRL | Qt::Key_W, m_canvasTabWidget, &CanvasTabWidget::closeCurrent);
    QAction* closeAllAction =fileMenu->addAction(tr("Close All"), Qt::CTRL | Qt::SHIFT | Qt::Key_W, m_canvasTabWidget, &CanvasTabWidget::closeAll);
    QAction* closeOthersAction = fileMenu->addAction(tr("Close Others"), Qt::CTRL | Qt::ALT | Qt::Key_W, m_canvasTabWidget, &CanvasTabWidget::closeOthers);

    fileMenu->addSeparator();
    fileMenu->addAction(tr("Exit"), Qt::CTRL | Qt::Key_Q, this, &QMainWindow::close);

    // Edit
    QMenu* editMenu = menuBar()->addMenu(tr("Edit"));

    auto undoAction = m_undoGroup->createUndoAction(this, tr("Undo"));
    undoAction->setShortcuts(QKeySequence::Undo);
    editMenu->addAction(undoAction);

    auto redoAction = m_undoGroup->createRedoAction(this, tr("Redo"));
    redoAction->setShortcuts(QKeySequence::Redo);
    editMenu->addAction(redoAction);

    QAction* clearAction = editMenu->addAction(tr("Clear"), Qt::Key_Delete, this, &MainWindow::clear);

    editMenu->addSeparator();
    editMenu->addAction(tr("Preferences..."), this, &MainWindow::showPreferences);

    // View
    m_viewMenu = menuBar()->addMenu(tr("View"));

    // Window
    QMenu* windowMenu = menuBar()->addMenu(tr("Window"));
    windowMenu->addAction(tr("Input Device..."), this, &MainWindow::showInputDevice);

    // Help
    QMenu* helpMenu = menuBar()->addMenu(tr("Help"));
    helpMenu->addAction(tr("About %1...").arg(Application::Name), this, &MainWindow::showAbout);

    connect(m_canvasTabWidget, &CanvasTabWidget::countChanged, this, [=] (int count) {
        saveAction->setEnabled(count);
        saveAsAction->setEnabled(count);
        exportAction->setEnabled(count);
        closeAction->setEnabled(count);
        closeAllAction->setEnabled(count);
        closeOthersAction->setEnabled(count >= 2);
        undoAction->setEnabled(count);
        redoAction->setEnabled(count);
        clearAction->setEnabled(count);
    });
}

void MainWindow::createUi() {
    createDockWindows();
}

void MainWindow::createDockWindows() {
    m_colorPicker = new ColorPicker;
    connect(m_colorPicker, &ColorPicker::colorChanged, m_brushEngine, &BrushEngine::setColor);
    connect(m_brushEngine, &BrushEngine::colorChanged, m_colorPicker, &ColorPicker::setColor);

    auto colorPickerDock = new QDockWidget(m_colorPicker->windowTitle(), this);
    colorPickerDock->setObjectName("color");
    colorPickerDock->setWidget(m_colorPicker);
    colorPickerDock->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);
    addDockWidget(Qt::RightDockWidgetArea, colorPickerDock);
    m_viewMenu->addAction(colorPickerDock->toggleViewAction());

    auto brushSettings = new BrushSettings(m_brushEngine);
    auto brushSettingsDock = new QDockWidget(brushSettings->windowTitle(), this);
    brushSettingsDock->setObjectName("brushSettings");
    brushSettingsDock->setWidget(brushSettings);
    brushSettingsDock->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);
    addDockWidget(Qt::RightDockWidgetArea, brushSettingsDock);
    m_viewMenu->addAction(brushSettingsDock->toggleViewAction());

    auto undoView = new QUndoView(m_undoGroup);
    auto undoViewDock = new QDockWidget(tr("Commands"), this);
    undoViewDock->setObjectName("commands");
    undoViewDock->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);
    undoViewDock->setWidget(undoView);
    addDockWidget(Qt::RightDockWidgetArea, undoViewDock);
    m_viewMenu->addAction(undoViewDock->toggleViewAction());
}

void MainWindow::applyHotSettings() {

}

Canvas* MainWindow::currentCanvas() const {
    return static_cast<Canvas*>(m_canvasTabWidget->currentWidget());
}
