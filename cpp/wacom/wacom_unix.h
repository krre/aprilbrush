#ifndef WACOM_H
#define WACOM_H

#include <QObject>

class Wacom : public QObject
{
public:
    Wacom();
    ~Wacom();
    qreal pressure();

private:
    void wacomInit();

    int pressureRange;
    unsigned int wacomId;
};

#endif // WACOM_H
