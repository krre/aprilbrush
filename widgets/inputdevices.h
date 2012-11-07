#ifndef INPUTDEVICES_H
#define INPUTDEVICES_H

#include <QtGui>
#include "../canvas.h"

class InputDevices : public QWidget
{
    Q_OBJECT

public:
    InputDevices(Canvas *canvas);

private:
    QLabel *infoLabel;
    Canvas *pCanvas;

private slots:
   void setInputValues();

};

#endif // TESTINPUTDEVICE_H
