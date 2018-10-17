#pragma once
#include <QObject>
#include <QVariantMap>

class TabletEventFilter : public QObject {
    Q_OBJECT

signals:
    void action(QVariantMap event);

public slots:

protected:
    bool eventFilter(QObject* obj, QEvent* event);
};

