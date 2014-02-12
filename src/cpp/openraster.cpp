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

#include "openraster.h"

OpenRaster::OpenRaster()
{
}

void OpenRaster::write(const QString oraPath, const QSize imageSize, const QVariantList layerList)
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

    QByteArray pixmapByteArray;
    QBuffer buffer(&pixmapByteArray);

    for (int i = 0; i < layerList.count(); i++) {
        QMap<QString, QVariant> map = layerList.at(i).toMap();
        // PNG file
        buffer.open(QIODevice::WriteOnly);
        QString layerId = map.value("layerId").toString();
        QPixmap *pixmap = m_imageProcessor->pixmapHash()[layerId];
        pixmap->save(&buffer, "PNG");
        buffer.close();
        QString name = map.value("name").toString();
        QString src = "data/" + name + ".png";
        zipWriter.addFile(src, pixmapByteArray);

        // layer
        stream.writeStartElement("layer");
        stream.writeAttribute("name", name);
        stream.writeAttribute("composite-op", "svg:src-over");
        QString enable = map.value("enable").toBool() ? "visible" : "";
        stream.writeAttribute("visibility", enable);
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

QVariantList OpenRaster::readAttributes(const QString oraPath)
{    
    QZipReader zipReader(oraPath, QIODevice::ReadOnly);

    QByteArray xmlByteArray = zipReader.fileData("stack.xml");
    QXmlStreamReader stream(xmlByteArray);
    QVariantMap map;
    QVariantList list;
    while (!stream.atEnd())
    {
        if (stream.isStartElement())
            if (stream.name() == "layer")
            {
                map["name"] = stream.attributes().value("name").toString();
                map["composite-op"] = stream.attributes().value("composite-op").toString();
                map["visibility"] = stream.attributes().value("visibility").toString();
                map["src"] = stream.attributes().value("src").toString();
                map["x"] = stream.attributes().value("x").toString();
                map["y"] = stream.attributes().value("y").toString();
                map["opacity"] = stream.attributes().value("opacity").toString();
                list.append(map);
            }

        stream.readNextStartElement();
    }
    zipReader.close();

    return list;
}

void OpenRaster::readPixmap(const QString oraPath, const QString pngPath, const QString layerId)
{
    QZipReader zipReader(oraPath, QIODevice::ReadOnly);
    QByteArray pngByteArray = zipReader.fileData(pngPath);
    QPixmap *pixmap = m_imageProcessor->pixmapHash()[layerId];
    pixmap->loadFromData(pngByteArray, "PNG");
    zipReader.close();
}

