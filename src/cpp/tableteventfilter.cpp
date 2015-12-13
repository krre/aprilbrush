#include "tableteventfilter.h"
#include <QtGui>

bool TabletEventFilter::eventFilter(QObject* obj, QEvent* event)
{
    if (event->type() == QEvent::TabletPress ||
            event->type() == QEvent::TabletMove ||
            event->type() == QEvent::TabletRelease ||
            event->type() == QEvent::TabletEnterProximity ||
            event->type() == QEvent::TabletLeaveProximity) {
        QTabletEvent* tabletEvent = static_cast<QTabletEvent*>(event);
        QVariantMap eventMap;
        eventMap["posX"] = tabletEvent->posF().x();
        eventMap["posY"] = tabletEvent->posF().y();
        eventMap["globalX"] = tabletEvent->hiResGlobalX();
        eventMap["globalY"] = tabletEvent->hiResGlobalY();
        eventMap["pressure"] = tabletEvent->pressure();
        eventMap["press"] = event->type() == QEvent::TabletPress;
        eventMap["release"] = event->type() == QEvent::TabletRelease;
        emit action(eventMap);
        return true;
    } else if (event->type() == QEvent::MouseMove) {
//        QMouseEvent* mouseEvent = static_cast<QMouseEvent*>(event);
        return QObject::eventFilter(obj, event);
    } else {
        // standard event processing
        return QObject::eventFilter(obj, event);
    }
}
