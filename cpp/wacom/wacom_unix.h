#ifndef WACOM_H
#define WACOM_H

#include <QObject>
#include "xcb/xcb.h"

#include <QAbstractNativeEventFilter>

class Wacom : public QObject
{
public:
    Wacom();
    ~Wacom();
    qreal pressure(); //{ return 1.0; }

private:
    void wacomInit();
    xcb_connection_t *xcbConnection;


};


class XcbEventFilter : public QAbstractNativeEventFilter
{
public:
    virtual bool nativeEventFilter(const QByteArray &eventType, void *message, long *) Q_DECL_OVERRIDE;

};

#endif // WACOM_H
