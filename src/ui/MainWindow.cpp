#include "MainWindow.h"
#include <QtWidgets>

MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent) {
    createActions();
    readSettings();
}

void MainWindow::closeEvent(QCloseEvent* event) {
    writeSettings();
    event->accept();
}

void MainWindow::readSettings() {
    QSettings settings;

    QByteArray geometry = settings.value("geometry", QByteArray()).toByteArray();

    if (geometry.isEmpty()) {
        QRect availableGeometry = QApplication::desktop()->availableGeometry(this);
        resize(availableGeometry.width() * 2 / 3, availableGeometry.height() * 2 / 3);
        move((availableGeometry.width() - width()) / 2, (availableGeometry.height() - height()) / 2);
    } else {
        restoreGeometry(geometry);
    }
}

void MainWindow::writeSettings() {
    QSettings settings;
    settings.setValue("geometry", saveGeometry());
}

void MainWindow::createActions() {
    QMenu* fileMenu = menuBar()->addMenu(tr("File"));
    fileMenu->addAction(tr("Exit"), this, &QMainWindow::close, QKeySequence("Ctrl+Q"));
}
