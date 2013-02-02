#include <QGuiApplication>
#include <QQuickView>
//#include "qtquickwindow.h"
//#include "paintspace.h"

//#include <QDeclarativeView>

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    //qmlRegisterType<PaintSpace>("Drawing", 1, 0, "PaintSpace");

    //QtQuickWindow window;
    //window.show();
    QQuickView view;
    view.setSource(QUrl::fromLocalFile("../aprilbrush/qml/main.qml"));
    view.setResizeMode(QQuickView::SizeRootObjectToView);
    //resize(1000, 200);
    view.show();

    return app.exec();
}
