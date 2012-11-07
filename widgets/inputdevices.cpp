#include "inputdevices.h"

InputDevices::InputDevices(Canvas *canvas)
{
    setWindowTitle(tr("Input Devices"));
    setFixedSize(250, 100);
    setWindowFlags(Qt::WindowStaysOnTopHint | Qt::Tool);
    infoLabel = new QLabel(this);
    infoLabel->resize(220, 80);
    pCanvas = canvas;
    connect(pCanvas, SIGNAL(inputEvent()), this, SLOT(setInputValues()));
    setInputValues();
}

void InputDevices::setInputValues()
{
    infoLabel->setText(QString(tr("  Input Device:\t")) + pCanvas->getTypeDevice()
                       + tr("\n  Pos X:\t\t") + QString::number(pCanvas->getVectorPoint().x())
                       + tr("\n  Pos Y:\t\t") + QString::number(pCanvas->getVectorPoint().y())
                       + tr("\n  Pressure:\t") + QString::number(pCanvas->getPressure()));
}


