/* AprilBrush - Digital Painting Software
 * Copyright (C) 2012-2013 Vladimir Zarypov <krre31@gmail.com>
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

#ifndef CORELIB_H
#define CORELIB_H

#include <QObject>
#include <QDebug>
#include <QVariant>
#include <QDate>
#include <QSize>

class CoreLib : public QObject
{
    Q_OBJECT

public:
    explicit CoreLib(QObject *parent = 0);
    Q_INVOKABLE QByteArray loadBrushPack();
    Q_INVOKABLE QVariant loadSettings();
    Q_INVOKABLE void saveSettings(QVariant settings);
    //Q_INVOKABLE void buildDate() { qDebug() << QLocale(QLocale::C).toDate(QString(__DATE__).simplified(), QLatin1String("MMM d yyyy")); }
    Q_INVOKABLE QString buildDate() { return QString(__DATE__); }
    Q_INVOKABLE QString rootFolder();

signals:

public slots:

};

#endif // CORELIB_H
