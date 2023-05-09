#include "InputDevice.h"
#include <QtWidgets>

InputDevice::InputDevice(QWidget* parent) : QWidget(parent) {
    setWindowTitle(tr("Input Device"));
    setFixedSize(250, 100);
    setWindowFlags(Qt::WindowStaysOnTopHint | Qt::Tool);
    setAttribute(Qt::WA_DeleteOnClose);
    
    m_type = new QLabel;
    m_posX = new QLabel;
    m_posY = new QLabel;
    m_pressure = new QLabel;

    auto formLayout = new QFormLayout;
    formLayout->addRow(tr("Type:"), m_type);
    formLayout->addRow(tr("Position X:"), m_posX);
    formLayout->addRow(tr("Position Y:"), m_posY);
    formLayout->addRow(tr("Pressure:"), m_pressure);

    setLayout(formLayout);
}

void InputDevice::onDataChanged(const Data& data) {
    m_type->setText(data.type == Type::Mouse ? tr("Mouse") : tr("Tablet"));
    m_posX->setText(QString::number(data.pos.x()));
    m_posY->setText(QString::number(data.pos.y()));
    m_pressure->setText(QString::number(data.pressure));
}
