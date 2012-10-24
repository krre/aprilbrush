#ifndef TESTINPUTDEVICE_H
#define TESTINPUTDEVICE_H

#include <QtGui>

class TestInputDevice : public QWidget
{
public:
    TestInputDevice();
    void setInputValues(QString typeDevice, int posX, int posY, float pressure);

private:
    QLabel *infoLabel;

};

#endif // TESTINPUTDEVICE_H
