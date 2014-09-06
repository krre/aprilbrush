#include "pointereater.h"
//#include <QTabletEvent>
//#include <QMouseEvent>
#include <QtGui>

PointerEater::PointerEater(QObject *parent) :
    QObject(parent)
{
}

bool PointerEater::eventFilter(QObject *obj, QEvent *event)
{
    if (event->type() == QEvent::TabletPress) {
        emit pressed(1);
        return QObject::eventFilter(obj, event);
    } else if (event->type() == QEvent::MouseButtonPress) {
        emit pressed(0);
        return QObject::eventFilter(obj, event);
    } else if (event->type() == QEvent::TabletMove) {
        QTabletEvent *tabletEvent = static_cast<QTabletEvent *>(event);
        emit pressure(tabletEvent->pressure());
        return true;
    } else {
        // standard event processing
        return QObject::eventFilter(obj, event);
    }
}
