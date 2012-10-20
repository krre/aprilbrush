#include "testinputdevice.h"

TestInputDevice::TestInputDevice() : QWidget()
{
    setWindowTitle("Test Input Device");
    resize(250, 100);
    setWindowFlags(Qt::WindowStaysOnTopHint | Qt::Tool);

    QLabel *infoLabel = new QLabel(this);
    infoLabel->setText(QString("  Input Device:\t") + "None"
                       + "\n  Pos X:\t\t" + "0"
                       + "\n  Pos Y:\t\t" + "0"
                       + "\n  Pressure:\t" + "0.0");
}

