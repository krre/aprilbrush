#include "testinputdevice.h"

TestInputDevice::TestInputDevice(Canvas *canvas)
{
    setWindowTitle(tr("Test Input Device"));
    setFixedSize(250, 100);
    setWindowFlags(Qt::WindowStaysOnTopHint | Qt::Tool);
    infoLabel = new QLabel(this);
    infoLabel->resize(220, 80);
    pCanvas = canvas;
    connect(pCanvas, SIGNAL(inputEvent()), this, SLOT(setInputValues()));
    setInputValues();
}

void TestInputDevice::setInputValues()
{
    infoLabel->setText(QString(tr("  Input Device:\t")) + pCanvas->getTypeDevice()
                       + tr("\n  Pos X:\t\t") + QString::number(pCanvas->getXPos())
                       + tr("\n  Pos Y:\t\t") + QString::number(pCanvas->getYPos())
                       + tr("\n  Pressure:\t") + QString::number(pCanvas->getPressure()));
}


