#include "corelib.h"
#include <QDebug>
#include <QDir>

CoreLib::CoreLib(QObject *parent) : QObject(parent)
{
}

void CoreLib::brushCount()
{
    qDebug() << QDir::currentPath();
}
