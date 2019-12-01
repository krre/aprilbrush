#include "MainWindow.h"
#include "CanvasTabWidget.h"
#include "NewImage.h"
#include "Options.h"
#include "core/Constants.h"
#include <QtWidgets>

MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent) {
    createActions();
    createUi();
    readSettings();
}

void MainWindow::closeEvent(QCloseEvent* event) {
    writeSettings();
    event->accept();
}

void MainWindow::createFile() {
    NewImage newImage;

    if (newImage.exec() == QDialog::Accepted) {
        canvasTabWidget->addCanvas(newImage.imageSize());
    }
}

void MainWindow::showAbout() {
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

void MainWindow::showOptions() {
    Options options;

    if (options.exec() == QDialog::Accepted) {
        applyHotSettings();
    }
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
    toolsMenu->addAction(tr("Options..."), this, &MainWindow::showOptions);

    // Help
    QMenu* helpMenu = menuBar()->addMenu(tr("Help"));
    helpMenu->addAction(tr("About %1...").arg(Const::App::Name), this, &MainWindow::showAbout);
}

void MainWindow::createUi() {
    canvasTabWidget = new CanvasTabWidget;
    setCentralWidget(canvasTabWidget);
}

void MainWindow::applyHotSettings() {

}
