#include "testinputdevice.h"

TestInputDevice::TestInputDevice()
{
    setWindowTitle(tr("Test Input Device"));
    resize(250, 100);
    setWindowFlags(Qt::WindowStaysOnTopHint | Qt::Tool);
    infoLabel = new QLabel(this);
    infoLabel->resize(220, 80);
    setInputValues(tr("None"), 0, 0, 1.0);
}

void TestInputDevice::setInputValues(QString typeDevice, int posX, int posY, float pressure)
{
    infoLabel->setText(QString(tr("  Input Device:\t")) + typeDevice
                       + tr("\n  Pos X:\t\t") + QString::number(posX)
                       + tr("\n  Pos Y:\t\t") + QString::number(posY)
                       + tr("\n  Pressure:\t") + QString::number(pressure));
}

