#include "tabletEventFilter.h"
#include <QtGui>

TabletEventFilter::TabletEventFilter(QObject *parent) :
    QObject(parent)
{
}

bool TabletEventFilter::eventFilter(QObject *obj, QEvent *event)
{
    if (event->type() == QEvent::TabletPress ||
            event->type() == QEvent::TabletMove ||
            event->type() == QEvent::TabletRelease ||
            event->type() == QEvent::TabletEnterProximity ||
            event->type() == QEvent::TabletLeaveProximity) {
        QTabletEvent *tabletEvent = static_cast<QTabletEvent *>(event);
        QVariantMap eventMap;
        eventMap["x"] = tabletEvent->hiResGlobalX();
        eventMap["y"] = tabletEvent->hiResGlobalY();
        eventMap["pressure"] = tabletEvent->pressure();
        eventMap["press"] = event->type() == QEvent::TabletPress;
        eventMap["release"] = event->type() == QEvent::TabletRelease;
        eventMap["enter"] = event->type() == QEvent::TabletEnterProximity;
        eventMap["leave"] = event->type() == QEvent::TabletLeaveProximity;
        emit action(eventMap);
        return true;
    } else {
        // standard event processing
        return QObject::eventFilter(obj, event);
    }
}
