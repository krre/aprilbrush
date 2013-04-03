#include "cpp/painteditem.h"
#include "cpp/brushengine.h"
#include "cpp/openraster.h"
#include "cpp/imageprocessor.h"
#include "cpp/corelib.h"

#include <QGuiApplication>
#include <QQuickView>

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    qmlRegisterType<PaintedItem>("PaintedItem", 1, 0, "PaintedItem");
    qmlRegisterType<BrushEngine>("BrushEngine", 1, 0, "BrushEngine");
    qmlRegisterType<OpenRaster>("OpenRaster", 1, 0, "OpenRaster");
    qmlRegisterType<ImageProcessor>("ImageProcessor", 1, 0, "ImageProcessor");
    qmlRegisterType<CoreLib>("CoreLib", 1, 0, "CoreLib");

    QQuickView view;
    view.setSource(QUrl::fromLocalFile("qml/main.qml"));
    view.setResizeMode(QQuickView::SizeRootObjectToView);
    view.show();

    return app.exec();
}
