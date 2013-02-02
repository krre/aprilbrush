#ifndef QMLWINDOW_H
#define QMLWINDOW_H
#include <QQuickView>

class QmlWindow : public QQuickView
{
    Q_OBJECT

public:
    QmlWindow();

protected:
    //void mouseMoveEvent(QMouseEvent *event);
    //void tabletEvent(QTabletEvent *event);

};

#endif // QMLWINDOW_H
