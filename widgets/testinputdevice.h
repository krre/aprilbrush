#ifndef TESTINPUTDEVICE_H
#define TESTINPUTDEVICE_H

#include <QtGui>
#include "../canvas.h"

class TestInputDevice : public QWidget
{
    Q_OBJECT

public:
    TestInputDevice(Canvas *canvas);

private:
    QLabel *infoLabel;
    Canvas *pCanvas;

private slots:
   void setInputValues();

};

#endif // TESTINPUTDEVICE_H
