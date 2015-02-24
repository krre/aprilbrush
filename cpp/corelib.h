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

#ifndef CORELIB_H
#define CORELIB_H

#include <QtCore>
#include <QtGui>

class CoreLib : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QWindow *window READ getWindow WRITE setWindow)
    Q_PROPERTY(QString buildDate READ getBuildDate CONSTANT)

public:
    explicit CoreLib(QObject *parent = 0);
    Q_INVOKABLE QByteArray loadBrushPack();
    Q_INVOKABLE QVariant loadSettings();
    Q_INVOKABLE void saveSettings(QVariant settings);
    //Q_INVOKABLE void buildDate() { qDebug() << QLocale(QLocale::C).toDate(QString(__DATE__).simplified(), QLatin1String("MMM d yyyy")); }
    Q_INVOKABLE void writeOra(const QString oraPath, const QSize imageSize, const QVariantList layerList);
    Q_INVOKABLE QVariantList readOra(const QString oraPath);
    Q_INVOKABLE void setCursorShape(QString type, int size);
    void setWindow(QWindow *window) { this->window = window; }
    QWindow * getWindow() { return this->window; }
    QString getBuildDate() { return QString(__DATE__); }

private:
    QPointer<QWindow> window;

};

#endif // CORELIB_H
