#include "corelib.h"
#include "qzip/qzipreader_p.h"

#include <QDir>

QSize CoreLib::m_screenSize;

CoreLib::CoreLib(QObject *parent) : QObject(parent)
{
}

QByteArray CoreLib::loadBrushPack()
{
    QString brushPresetsPath = QDir::currentPath() + "/presets/brushes";
    QString defaultBrushPackPath = brushPresetsPath + "/default.abb";
    QZipReader zipReader(defaultBrushPackPath, QIODevice::ReadOnly);
    QByteArray jsonArray = zipReader.fileData("default.json");
    zipReader.close();
    return jsonArray;
}

QVariant CoreLib::loadSettings()
{
    QString settingsPath = QDir::currentPath() + "/.aprilbrush/settings.json";
    if (!QFile::exists(settingsPath))
        return 0;

    QFile file(settingsPath);
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    QByteArray byteArray;
    while (!file.atEnd())
        byteArray.append(file.readLine());

    return byteArray;
}

void CoreLib::saveSettings(QVariant settings)
{
    QString settingsDirPath = QDir::currentPath() + "/.aprilbrush";
    if (!QDir(settingsDirPath).exists())
        QDir().mkdir(settingsDirPath);
    QString settingsPath = settingsDirPath + "/settings.json";

    QFile file(settingsPath);
    file.open(QIODevice::WriteOnly | QIODevice::Text);
    QTextStream out(&file);
    out << settings.toString();
    file.close();
}

