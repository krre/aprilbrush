#ifndef INPUTDEVICES_H
#define INPUTDEVICES_H

#include <QtGui>
#include "../canvas.h"

class InputDevices : public QWidget
{
    Q_OBJECT

public:
    InputDevices(Canvas *appCanvas);

private:
    QLabel *infoLabel;
    Canvas *canvas;

private slots:
   void setInputValuesSlot();

};

#endif // TESTINPUTDEVICE_H
