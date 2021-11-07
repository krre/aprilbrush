#pragma once
#include <QObject>

class SignalHub : public QObject {
    Q_OBJECT
public:
    SignalHub(QObject* parent);
    static SignalHub* instance();

signals:
    void inputDeviceValueChanged(const QVariantMap& value);

private:

};

