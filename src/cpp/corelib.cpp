/* AprilBrush - Digital Painting Software
 * Copyright (C) 2012-2014 Vladimir Zarypov <krre31@gmail.com>
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation;
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 */

#include "corelib.h"
#include "qzip/qzipreader_p.h"

#include <QDir>

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

QString CoreLib::rootFolder()
{
#ifdef Q_OS_WIN
    return "file:/c:/";
#endif

#ifdef Q_OS_UNIX
    return "file:/";
#endif
}

