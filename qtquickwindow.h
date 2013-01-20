#ifndef QTQUICKWINDOW_H
#define QTQUICKWINDOW_H

#include <QDeclarativeView>
#include <QtGui>
#include "brushengine.h"

class QtQuickWindow : public QDeclarativeView
{
    Q_OBJECT

public:
    QtQuickWindow(QWidget *parent = 0);

protected:
//    void tabletEvent(QTabletEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
//    void mousePressEvent(QMouseEvent *event);
//    void mouseReleaseEvent(QMouseEvent *event);

private:
    BrushEngine brushEngine;

};

#endif // QTQUICKWINDOW_H
