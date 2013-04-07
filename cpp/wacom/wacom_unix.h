#ifndef WACOM_H
#define WACOM_H

#include <QObject>

class Wacom : public QObject
{
public:
    Wacom();
    qreal pressure() { return 1.0; }
};

#endif // WACOM_H
