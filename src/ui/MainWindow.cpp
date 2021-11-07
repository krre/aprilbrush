#include "MainWindow.h"
#include "CanvasTabWidget.h"
#include "NewImage.h"
#include "Options.h"
#include "Canvas.h"
#include "InputDevice.h"
#include "ColorPicker.h"
#include "core/Context.h"
#include "core/SignalHub.h"
#include "core/Constants.h"
#include <QtWidgets>

MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent) {
    setAutoFillBackground(true);

    new SignalHub(this);
    new Context(this);

    createActions();
    createUi();
    readSettings();
    canvasTabWidget->addCanvas();
}

void MainWindow::closeEvent(QCloseEvent* event) {
    writeSettings();
    event->accept();
}

void MainWindow::createFile() {
    NewImage newImage(canvasTabWidget->nextName());

    if (newImage.exec() == QDialog::Accepted) {
        canvasTabWidget->addCanvas(newImage.name(), newImage.size());
    }
}

void MainWindow::onAbout() {
    using namespace Const::App;

    QMessageBox::about(this, tr("About %1").arg(Name),
        tr("<h3>%1 %2</h3>"
           "Painting application<br><br>"
           "Based on Qt %3<br>"
           "Build on %4 %5<br><br>"
           "<a href=%6>%6</a><br><br>"
           "Copyright © 2012-%7, Vladimir Zarypov")
           .arg(Name, Version, QT_VERSION_STR, BuildDate, BuildTime, URL, CopyrightLastYear));
}

void MainWindow::onOptions() {
    Options options;

    if (options.exec() == QDialog::Accepted) {
        applyHotSettings();
    }
}

void MainWindow::onInputDevice() {
    auto inputDevice = new InputDevice(this);
    inputDevice->show();
}

void MainWindow::readSettings() {
    QSettings settings;
    QByteArray geometry = settings.value("geometry", QByteArray()).toByteArray();

    if (geometry.isEmpty()) {
        QSize screenSize = QGuiApplication::screens().first()->size();
        resize(screenSize.width() * 2 / 3, screenSize.height() * 2 / 3);
        move((screenSize.width() - width()) / 2, (screenSize.height() - height()) / 2);
    } else {
        restoreGeometry(geometry);
    }
}

void MainWindow::writeSettings() {
    QSettings settings;
    settings.setValue("geometry", saveGeometry());
}

void MainWindow::createActions() {
    // File
    QMenu* fileMenu = menuBar()->addMenu(tr("File"));
    fileMenu->addAction(tr("New..."), this, &MainWindow::createFile, QKeySequence("Ctrl+N"));
    fileMenu->addSeparator();
    fileMenu->addAction(tr("Exit"), this, &QMainWindow::close, QKeySequence("Ctrl+Q"));

    // Tools
    QMenu* toolsMenu = menuBar()->addMenu(tr("Tools"));
    toolsMenu->addAction(tr("Options..."), this, &MainWindow::onOptions);

    // View
    viewMenu = menuBar()->addMenu(tr("View"));

    // Window
    QMenu* windowMenu = menuBar()->addMenu(tr("Window"));
    windowMenu->addAction(tr("Input Device..."), this, &MainWindow::onInputDevice);

    // Help
    QMenu* helpMenu = menuBar()->addMenu(tr("Help"));
    helpMenu->addAction(tr("About %1...").arg(Const::App::Name), this, &MainWindow::onAbout);
}

void MainWindow::createUi() {
    canvasTabWidget = new CanvasTabWidget;
    setCentralWidget(canvasTabWidget);

    createDockWindows();
}

void MainWindow::createDockWindows() {
    auto colorPicker = new ColorPicker;
    Context::setColorPicker(colorPicker);
    auto dock = new QDockWidget(colorPicker->windowTitle(), this);
    dock->setWidget(colorPicker);
    dock->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);
    addDockWidget(Qt::RightDockWidgetArea, dock);
    viewMenu->addAction(dock->toggleViewAction());
}

void MainWindow::applyHotSettings() {

}
