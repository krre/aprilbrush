#include "qtquickwindow.h"
//#include <QDeclarativeComponent>
//#include <QDeclarativeEngine>
//#include <QDeclarativeContext>

QtQuickWindow::QtQuickWindow(QWidget *parent) : QDeclarativeView(parent)
{
    //setSource(QUrl("qrc:qml/qml/main.qml"));
    setSource(QUrl("../../Projects/aprilbrush/qml/main.qml"));
    setResizeMode(QDeclarativeView::SizeRootObjectToView);
    setWindowIcon(QIcon(":/icons/Butterfly_128x128.png"));

    //connect(engine(), SIGNAL(quit()), this, SLOT(close()));

    int startWindowWidth = qApp->desktop()->width() * 0.9;
    int startWindowHeight = qApp->desktop()->height() * 0.85;
    resize(startWindowWidth, startWindowHeight);

    //BrushEngine brushEngine;
}

//void QtQuickWindow::tabletEvent(QTabletEvent *event)
//{
//}


void QtQuickWindow::mouseMoveEvent(QMouseEvent *event)
{
    //qDebug() << event->x();


}

//void QtQuickWindow::mousePressEvent(QMouseEvent *event)
//{
//}

//void QtQuickWindow::mouseReleaseEvent(QMouseEvent *event)
//{
//}


