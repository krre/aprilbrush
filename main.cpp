#include <QGuiApplication>
#include <QQuickView>
#include "qmlwindow.h"
#include "paintspace.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    qmlRegisterType<PaintSpace>("Drawing", 1, 0, "PaintSpace");

    QmlWindow window;
    window.show();

    return app.exec();
}
