#include <QGuiApplication>
#include <QQuickView>
#include <QtGui>
#include "cpp/painteditem.h"
#include "cpp/brushengine.h"
#include "cpp/openraster/openraster.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    qmlRegisterType<PaintedItem>("PaintedItem", 1, 0, "PaintedItem");
    qmlRegisterType<BrushEngine>("BrushEngine", 1, 0, "Brush");
    qmlRegisterType<OpenRaster>("OpenRaster", 1, 0, "OpenRaster");

    QQuickView view;
    //view.setSource(QUrl::fromLocalFile("qml/main.qml"));
    view.setSource(QUrl::fromLocalFile("../../aprilbrush/qml/main.qml"));
    view.setResizeMode(QQuickView::SizeRootObjectToView);
    view.show();

    //QQuickItem *item = view.rootObject()->findChild<QQuickItem*>("main1");
    //QQuickItem *item = view.rootObject()->findChild<QQuickItem*>("main");
    //qDebug() << "main.cpp: " << view.rootObject()->findChild<QQuickItem*>();

    return app.exec();
}
