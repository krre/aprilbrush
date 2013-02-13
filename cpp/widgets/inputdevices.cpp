#include "inputdevices.h"

InputDevices::InputDevices(Canvas *appCanvas)
{
    setWindowTitle(tr("Input Devices"));
    setFixedSize(250, 100);
    setWindowFlags(Qt::WindowStaysOnTopHint | Qt::Tool);
    infoLabel = new QLabel(this);
    infoLabel->resize(220, 80);
    canvas = appCanvas;
    connect(canvas, SIGNAL(inputEventSignal()), this, SLOT(setInputValuesSlot()));
    setInputValuesSlot();
}

void InputDevices::setInputValuesSlot()
{
    infoLabel->setText(QString(tr("  Input Device:\t")) + canvas->typeDevice()
                       + tr("\n  Pos X:\t\t") + QString::number(canvas->posCursor().x())
                       + tr("\n  Pos Y:\t\t") + QString::number(canvas->posCursor().y())
                       + tr("\n  Pressure:\t") + QString::number(canvas->pressure()));
}


