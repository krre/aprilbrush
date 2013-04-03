#include "corelib.h"
#include "qzip/qzipreader_p.h"

#include <QDebug>
#include <QDir>

CoreLib::CoreLib(QObject *parent) : QObject(parent)
{
}

QByteArray CoreLib::brushPack()
{
    QString brushPresetsPath = QDir::currentPath() + "/presets/brushes";
    QString defaultBrushPackPath = brushPresetsPath + "/default.abb";
    QZipReader zipReader(defaultBrushPackPath, QIODevice::ReadOnly);
    QByteArray jsonArray = zipReader.fileData("default.json");
    zipReader.close();
    return jsonArray;
}
