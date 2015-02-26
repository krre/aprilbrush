#include "tabletEventFilter.h"
#include <QtGui>

TabletEventFilter::TabletEventFilter(QObject *parent) :
    QObject(parent)
{
}

bool TabletEventFilter::eventFilter(QObject *obj, QEvent *event)
{
    if (event->type() == QEvent::TabletPress) {
        QTabletEvent *tabletEvent = static_cast<QTabletEvent *>(event);
        emit pressure(tabletEvent->pressure());
        return true;
    } else if (event->type() == QEvent::TabletMove) {
        QTabletEvent *tabletEvent = static_cast<QTabletEvent *>(event);
        qreal pressureValue = tabletEvent->pressure();
        if (pressureValue) {
            emit pressure(pressureValue);
        }
        return true;
    } else {
        // standard event processing
        return QObject::eventFilter(obj, event);
    }
}
