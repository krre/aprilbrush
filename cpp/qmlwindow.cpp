#include "qmlwindow.h"
#include <QtGui>

QmlWindow::QmlWindow()
{
    setSource(QUrl::fromLocalFile("qml/main.qml"));
    //setSource(QUrl::fromLocalFile("../aprilbrush/qml/ColorPicker.qml"));
    setResizeMode(QQuickView::SizeRootObjectToView);
    //setPosition(150, 150);
}
