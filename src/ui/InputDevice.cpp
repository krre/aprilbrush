#include "InputDevice.h"
#include "core/SignalHub.h"
#include <QtWidgets>

InputDevice::InputDevice(QWidget* parent) : QWidget(parent) {
    setWindowTitle(tr("Input Device"));
    setFixedSize(250, 100);
    setWindowFlags(Qt::WindowStaysOnTopHint | Qt::Tool);
    setAttribute(Qt::WA_DeleteOnClose);

    type = new QLabel;
    posX = new QLabel;
    posY = new QLabel;
    pressure = new QLabel;

    auto formLayout = new QFormLayout;
    formLayout->addRow(tr("Type:"), type);
    formLayout->addRow(tr("Position X:"), posX);
    formLayout->addRow(tr("Position Y:"), posY);
    formLayout->addRow(tr("Pressure:"), pressure);

    setLayout(formLayout);
    connect(SignalHub::instance(), &SignalHub::inputDeviceValueChanged, this, &InputDevice::onInputDeviceValueChanged);

}

void InputDevice::onInputDeviceValueChanged(const QVariantMap& value) {
    type->setText(value["type"].toString());
    posX->setText(QString::number(value["position"].toPointF().x()));
    posY->setText(QString::number(value["position"].toPointF().y()));
    pressure->setText(QString::number(value["pressure"].toDouble()));
}
