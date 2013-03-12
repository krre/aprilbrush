#include <QGuiApplication>
#include <QQuickView>
#include "cpp/paintspace.h"
#include "cpp/brushengine.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    qmlRegisterType<PaintSpace>("PaintItem", 1, 0, "PaintSpace");
    qmlRegisterType<BrushEngine>("BrushEngine", 1, 0, "Brush");

    QQuickView view;
    //view.setSource(QUrl::fromLocalFile("qml/main.qml"));
    view.setSource(QUrl::fromLocalFile("../../aprilbrush/qml/main.qml"));
    view.setResizeMode(QQuickView::SizeRootObjectToView);
    view.show();

    return app.exec();
}
