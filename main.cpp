#include "cpp/painteditem.h"
#include "cpp/brushengine.h"
#include "cpp/openraster.h"
#include "cpp/imageprocessor.h"
#include "cpp/corelib.h"

#include <QGuiApplication>
#include <QQuickView>
#include <QtQml>
#include <QDebug>
#include <QScreen>

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    qmlRegisterType<PaintedItem>("AprilBrushLib", 1, 0, "PaintedItem");
    qmlRegisterType<BrushEngine>("AprilBrushLib", 1, 0, "BrushEngine");
    qmlRegisterType<OpenRaster>("AprilBrushLib", 1, 0, "OpenRaster");
    qmlRegisterType<ImageProcessor>("AprilBrushLib", 1, 0, "ImageProcessor");
    qmlRegisterType<CoreLib>("AprilBrushLib", 1, 0, "CoreLib");

    QQuickView view;
    QScreen *screen = view.screen();
    CoreLib::m_screenSize = screen->size();
    view.setSource(QUrl::fromLocalFile("qml/main.qml"));
    view.setResizeMode(QQuickView::SizeRootObjectToView);
    view.show();

    return app.exec();
}
