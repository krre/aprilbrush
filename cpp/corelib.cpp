#include "corelib.h"
#include <QDebug>
#include <QDir>

CoreLib::CoreLib(QObject *parent) : QObject(parent)
{
}

void CoreLib::brushCount()
{
    //qDebug() << QDir::currentPath();
    QString brushPresetsPath = QDir::currentPath() + "/presets/brushes";
    QString defaultBrushPack = brushPresetsPath + "/default.abb";
    qDebug() << defaultBrushPack;
}
