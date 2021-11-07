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
    connect(SignalHub::instance(), &SignalHub::inputDeviceDataChanged, this, &InputDevice::onDataChanged);
}

void InputDevice::onDataChanged(const Data& data) {
    type->setText(data.type == Type::Mouse ? tr("Mouse") : tr("Tablet"));
    posX->setText(QString::number(data.pos.x()));
    posY->setText(QString::number(data.pos.y()));
    pressure->setText(QString::number(data.pressure));
}
