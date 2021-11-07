#pragma once
#include "ui/InputDevice.h"
#include <QObject>

class SignalHub : public QObject {
    Q_OBJECT
public:
    SignalHub(QObject* parent);
    static SignalHub* instance();

signals:
    void inputDeviceDataChanged(const InputDevice::Data& data);
};
