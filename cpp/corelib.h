#ifndef CORELIB_H
#define CORELIB_H

#include <QObject>

class CoreLib : public QObject
{
    Q_OBJECT

public:
    explicit CoreLib(QObject *parent = 0);
    Q_INVOKABLE void brushCount();
    
signals:
    
public slots:
    
};

#endif // CORELIB_H
