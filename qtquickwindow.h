#ifndef QTQUICKWINDOW_H
#define QTQUICKWINDOW_H

//#include <QDeclarativeView>
//#include <QtWidgets>
#include <QQuickView>
#include "brushengine.h"

class QtQuickWindow : public QQuickView
{
    Q_OBJECT

public:
    QtQuickWindow();

protected:
//    void tabletEvent(QTabletEvent *event);
//    void mouseMoveEvent(QMouseEvent *event);
//    void mousePressEvent(QMouseEvent *event);
//    void mouseReleaseEvent(QMouseEvent *event);


private:
    BrushEngine brushEngine;

};

#endif // QTQUICKWINDOW_H
