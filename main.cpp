#include "cpp/painteditem.h"
#include "cpp/brushengine.h"
#include "cpp/openraster.h"
#include "cpp/imageprocessor.h"
#include "cpp/corelib.h"
#ifdef Q_OS_UNIX
#include "cpp/wacom/wacom_unix.h"
#endif

#include <QGuiApplication>
#include <QQuickView>
#include <QtQml>

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    qmlRegisterType<PaintedItem>("PaintedItem", 1, 0, "PaintedItem");
    qmlRegisterType<BrushEngine>("BrushEngine", 1, 0, "BrushEngine");
    qmlRegisterType<OpenRaster>("OpenRaster", 1, 0, "OpenRaster");
    qmlRegisterType<ImageProcessor>("ImageProcessor", 1, 0, "ImageProcessor");
    qmlRegisterType<CoreLib>("CoreLib", 1, 0, "CoreLib");

#ifdef Q_OS_UNIX
    XcbEventFilter *filter = new XcbEventFilter();
    app.eventDispatcher()->installNativeEventFilter(filter);
#endif

    qDebug() << app.platformName();

    QQuickView view;
    view.setSource(QUrl::fromLocalFile("qml/main.qml"));
    view.setResizeMode(QQuickView::SizeRootObjectToView);
    view.show();

    return app.exec();
}
