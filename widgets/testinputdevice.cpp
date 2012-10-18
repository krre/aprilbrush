#include "testinputdevice.h"

TestInputDevice::TestInputDevice() : QWidget()
{
    setWindowTitle("Test Input Device");
    resize(250, 100);
    setWindowFlags(Qt::WindowStaysOnTopHint | Qt::Tool);

    QLabel *nameDeviceLabel = new QLabel(this);
    nameDeviceLabel->setText("Input Device:");
    QLabel *nameDeviceValue = new QLabel(this);
    nameDeviceValue->setText("None");
    QLabel *xPosLabel = new QLabel(this);
    xPosLabel->setText("Pos X:");
    QLabel *xPosValue = new QLabel(this);
    xPosValue->setText("0.000");
    QLabel *yPosLabel = new QLabel(this);
    yPosLabel->setText("Pos Y:");
    QLabel *yPosValue = new QLabel(this);
    yPosValue->setText("0.000");
    QLabel *pressureLabel = new QLabel(this);
    pressureLabel->setText("Pressure:");
    QLabel *pressureValue = new QLabel(this);
    pressureValue->setText("0.000");

    QGridLayout *gridLayout = new QGridLayout(this);
    gridLayout->addWidget(nameDeviceLabel, 0, 0);
    gridLayout->addWidget(nameDeviceValue, 0, 1);
    gridLayout->addWidget(xPosLabel, 1, 0);
    gridLayout->addWidget(xPosValue, 1, 1);
    gridLayout->addWidget(yPosLabel, 2, 0);
    gridLayout->addWidget(yPosValue, 2, 1);
    gridLayout->addWidget(pressureLabel, 3, 0);
    gridLayout->addWidget(pressureValue, 3, 1);
}

