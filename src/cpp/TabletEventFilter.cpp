#include "TabletEventFilter.h"
#include <QtGui>

namespace AprilBrush {

bool TabletEventFilter::eventFilter(QObject* obj, QEvent* event) {
    if (event->type() == QEvent::TabletPress ||
            event->type() == QEvent::TabletMove ||
            event->type() == QEvent::TabletRelease ||
            event->type() == QEvent::TabletEnterProximity ||
            event->type() == QEvent::TabletLeaveProximity) {
        QTabletEvent* tabletEvent = static_cast<QTabletEvent*>(event);
        QVariantMap map;
        map["posX"] = tabletEvent->posF().x();
        map["posY"] = tabletEvent->posF().y();
        map["globalX"] = tabletEvent->hiResGlobalX();
        map["globalY"] = tabletEvent->hiResGlobalY();
        map["pressure"] = tabletEvent->pressure();
        map["press"] = event->type() == QEvent::TabletPress;
        map["release"] = event->type() == QEvent::TabletRelease;
        emit action(map);
        return true;
    } else if (event->type() == QEvent::MouseMove) {
//        QMouseEvent* mouseEvent = static_cast<QMouseEvent*>(event);
        return QObject::eventFilter(obj, event);
    } else {
        // standard event processing
        return QObject::eventFilter(obj, event);
    }
}

} // AprilBrush
