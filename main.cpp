#include <QGuiApplication>
#include <QQuickView>
#include "cpp/qmlwindow.h"
#include "cpp/paintspace.h"
#include "cpp/brushengine.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    qmlRegisterType<PaintSpace>("Drawing", 1, 0, "PaintSpace");
    qmlRegisterType<BrushEngine>("BrushEngine", 1, 0, "Brush");

    QmlWindow window;
    window.show();

    return app.exec();
}
