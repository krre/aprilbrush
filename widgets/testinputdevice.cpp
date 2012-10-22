#include "testinputdevice.h"

TestInputDevice::TestInputDevice() : QWidget()
{
    setWindowTitle(tr("Test Input Device"));
    resize(250, 100);
    setWindowFlags(Qt::WindowStaysOnTopHint | Qt::Tool);

    QLabel *infoLabel = new QLabel(this);
    infoLabel->setText(QString(tr("  Input Device:\t")) + tr("None")
                       + tr("\n  Pos X:\t\t") + "0"
                       + tr("\n  Pos Y:\t\t") + "0"
                       + tr("\n  Pressure:\t") + "0.0");
}

