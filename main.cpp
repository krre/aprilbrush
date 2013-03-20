#include <QGuiApplication>
#include <QQuickView>
#include "cpp/painteditem.h"
#include "cpp/brushengine.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    qmlRegisterType<PaintedItem>("PaintedItem", 1, 0, "PaintedItem");
    qmlRegisterType<BrushEngine>("BrushEngine", 1, 0, "Brush");

    QQuickView view;
    //view.setSource(QUrl::fromLocalFile("qml/main.qml"));
    view.setSource(QUrl::fromLocalFile("../../aprilbrush/qml/main.qml"));
    view.setResizeMode(QQuickView::SizeRootObjectToView);
    view.show();

    return app.exec();
}
