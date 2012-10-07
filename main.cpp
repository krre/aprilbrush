#include <QApplication>
#include <QMainWindow>

const QString appName = "AprilBrush";

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    QMainWindow *mainWindow = new QMainWindow();
    mainWindow->setWindowTitle(appName);
    mainWindow->show();

    return app.exec();
}
