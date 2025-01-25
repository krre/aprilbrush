#include "InputDevice.h"
#include "settings/Settings.h"
#include <QLabel>
#include <QFormLayout>
#include <QCloseEvent>

InputDevice::InputDevice(Settings* settings, QWidget* parent) : QWidget(parent), m_settings(settings) {
    setWindowTitle(tr("Input Device"));
    setFixedSize(250, 100);
    setWindowFlags(Qt::WindowStaysOnTopHint | Qt::Tool);
    setAttribute(Qt::WA_DeleteOnClose);

    m_type = new QLabel;
    m_position = new QLabel;
    m_pressure = new QLabel;

    auto formLayout = new QFormLayout;
    formLayout->addRow(tr("Type:"), m_type);
    formLayout->addRow(tr("Position:"), m_position);
    formLayout->addRow(tr("Pressure:"), m_pressure);

    setLayout(formLayout);

    readSettings();
}

void InputDevice::setData(const Data& data) {
    m_type->setText(data.type == Type::Mouse ? tr("Mouse") : tr("Tablet"));
    m_position->setText(QString("%1, %2").arg(data.position.x()).arg(data.position.y()));
    m_pressure->setText(QString::number(data.pressure));
}

void InputDevice::closeEvent(QCloseEvent* event) {
    writeSettings();
    event->accept();
}

void InputDevice::readSettings() {
    QByteArray geometry = m_settings->inputDeviceGeometry();

    if (!geometry.isEmpty()) {
        restoreGeometry(geometry);
    }
}

void InputDevice::writeSettings() {
    m_settings->setInputDeviceGeometry(saveGeometry());
}
