#ifndef CORELIB_H
#define CORELIB_H

#include <QObject>

#include <QVariant>
#include <QCoreApplication>

class CoreLib : public QObject
{
    Q_OBJECT

public:
    explicit CoreLib(QObject *parent = 0);
    Q_INVOKABLE QByteArray loadBrushPack();
    Q_INVOKABLE QVariant loadSettings();
    Q_INVOKABLE void saveSettings(QVariant settings);
    
signals:
    
public slots:
    
};

#endif // CORELIB_H
