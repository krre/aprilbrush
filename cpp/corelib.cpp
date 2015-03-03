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
#include "tableteventfilter.h"
#include "qzip/qzipreader_p.h"
#include "qzip/qzipwriter_p.h"

#include <QtGui>
#include <QtQuick>
#include <QDir>
#include <QCursor>
#include <QXmlStreamReader>
#include <QXmlStreamWriter>

extern QPointer<TabletEventFilter> tabletEventFilter;

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
    QString settingsPath = QDir::currentPath() + "/profile/settings.json";
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
    QString settingsDirPath = QDir::currentPath() + "/profile";
    if (!QDir(settingsDirPath).exists())
        QDir().mkdir(settingsDirPath);
    QString settingsPath = settingsDirPath + "/settings.json";

    QFile file(settingsPath);
    file.open(QIODevice::WriteOnly | QIODevice::Text);
    QTextStream out(&file);
    out << settings.toString();
    file.close();
}

void CoreLib::writeOra(const QString oraPath, const QSize imageSize, const QVariantList layerList)
{
    QZipWriter zipWriter(oraPath);
    zipWriter.setCompressionPolicy(QZipWriter::AutoCompress);

    QByteArray xmlByteArray;

    // mimetype file
    xmlByteArray.append("image/openraster");
    zipWriter.addFile("mimetype", xmlByteArray);

    // stack.xml file
    QXmlStreamWriter stream(&xmlByteArray);
    stream.setAutoFormatting(true);

    stream.writeStartDocument();

    stream.writeStartElement("image");
    stream.writeAttribute("w", QString::number(imageSize.width()));
    stream.writeAttribute("h",QString::number(imageSize.height()));
    stream.writeStartElement("stack");

    for (int i = 0; i < layerList.count(); i++) {
        QMap<QString, QVariant> map = layerList.at(i).toMap();
        QString name = map.value("name").toString();
        QString isVisible = map.value("isVisible").toString();
        QString isLock = map.value("isLock").toString();
        QString isBackground = map.value("isBackground").toString();
        QString isSelected = map.value("isSelected").toString();
        QByteArray imageByteArray = QByteArray::fromBase64(map.value("image").toByteArray());
        QString src = "data/" + name + ".png";
        zipWriter.addFile(src, imageByteArray);

        // layer
        stream.writeStartElement("layer");
        stream.writeAttribute("name", name);
        stream.writeAttribute("composite-op", "svg:src-over");
        stream.writeAttribute("visibility", isVisible == "true" ? "visible" : "hidden");
        stream.writeAttribute("edit-locked", isLock);
        stream.writeAttribute("selected", isSelected);
        stream.writeAttribute("aprilbrush_background", isBackground);
        stream.writeAttribute("src", src);
        stream.writeAttribute("x", "0");
        stream.writeAttribute("y", "0");
        stream.writeAttribute("opacity", "1.0");
        stream.writeEndElement(); // layer
    }

    stream.writeEndElement(); // stack
    stream.writeEndElement(); // image
    stream.writeEndDocument(); // document
    zipWriter.addFile("stack.xml", xmlByteArray);

    zipWriter.close();
}

QVariantList CoreLib::readOra(const QString oraPath) {
    QZipReader zipReader(oraPath, QIODevice::ReadOnly);

    QByteArray xmlByteArray = zipReader.fileData("stack.xml");
    QXmlStreamReader stream(xmlByteArray);
    QVariantMap map;
    QVariantList list;

    while (!stream.atEnd()) {
        if (stream.isStartElement()) {
            if (stream.name() == "layer") {
                for (int i = 0; i < stream.attributes().size(); i++) {
                    map[stream.attributes().at(i).name().toString()] = stream.attributes().at(i).value().toString();
                }
                QByteArray byteArray = zipReader.fileData(stream.attributes().value("src").toString());
                QString dataURL = QString("data:image/png;base64," + byteArray.toBase64());
                map["image"] = dataURL;
                list.append(map);
                map.clear();
            }
        }
        stream.readNextStartElement();
    }
    zipReader.close();

    return list;
}

void CoreLib::setCursorShape(QString type, int size=0)
{
    if (!window) {
        return;
    }
    if (type == "Paint") {
         // size of the cursor should not be very small
        int sizeBrush = qMax(size, 3);

        QPixmap pixmap(sizeBrush, sizeBrush);
        pixmap.fill(QColor(255, 255, 255, 0));
        QPainter painter(&pixmap);
        painter.setRenderHint(QPainter::Antialiasing, true);
        painter.setBrush(Qt::NoBrush);
        painter.setPen(QColor(0, 0, 0, 200));
        painter.drawEllipse(0, 0, sizeBrush, sizeBrush);
        painter.setPen(QColor(255, 255, 255, 200));
        painter.drawEllipse(1, 1, sizeBrush - 2, sizeBrush - 2);
        window->setCursor(pixmap);
    } else if (type == "OpenHand") {
        QCursor cursor = QCursor(Qt::OpenHandCursor);
        window->setCursor(cursor);
    } else if (type == "PickColor") {
        QCursor cursor = QCursor(Qt::CrossCursor);
        window->setCursor(cursor);
    } else if (type == "Arrow") {
        QCursor cursor = QCursor(Qt::ArrowCursor);
        window->setCursor(cursor);
    }
}

void CoreLib::addEventFilter(QVariant item)
{
    QObject *obj = qvariant_cast<QObject *>(item);
    QQuickWindow *wnd = qobject_cast<QQuickWindow *>(obj);
    wnd->installEventFilter(tabletEventFilter);
}
