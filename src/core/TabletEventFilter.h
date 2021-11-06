#pragma once
#include <QObject>
#include <QVariantMap>

class TabletEventFilter : public QObject {
    Q_OBJECT
signals:
    void action(QVariantMap event);

protected:
    bool eventFilter(QObject* obj, QEvent* event);
};

