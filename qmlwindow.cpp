#include "qmlwindow.h"
#include <QDebug>

QmlWindow::QmlWindow()
{
    setSource(QUrl::fromLocalFile("../aprilbrush/qml/main.qml"));
    setResizeMode(QQuickView::SizeRootObjectToView);
    setPosition(100, 100);
}
/*
void QmlWindow::mouseMoveEvent(QMouseEvent *event)
{
    qDebug() << event->pos();
}
*/

/*
void QmlWindow::tabletEvent(QTabletEvent *event)
{
    qDebug() << event->pos() << event->pressure();
}
*/
