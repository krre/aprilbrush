#include <QApplication>
#include "qtquickwindow.h"
#include "paintspace.h"

#include <QDeclarativeView>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    qmlRegisterType<PaintSpace>("Drawing", 1, 0, "PaintSpace");

    QtQuickWindow window;
    window.show();

    return app.exec();
}
