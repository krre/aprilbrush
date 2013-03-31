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

        qDebug() << name << layerId << enable;
    }

    stream.writeEndElement(); // stack
    stream.writeEndElement(); // image
    stream.writeEndDocument(); // document
    zipWriter.addFile("stack.xml", xmlByteArray);

    zipWriter.close();
}

void OpenRaster::readAttributes(const QString oraPath)
{    
    QZipReader zipReader(oraPath, QIODevice::ReadOnly);

    QByteArray xmlByteArray = zipReader.fileData("stack.xml");
    QXmlStreamReader stream(xmlByteArray);
    while (!stream.atEnd())
    {
        if (stream.isStartElement())
            if (stream.name() == "layer")
            {
                    //qDebug() << stream.attributes().value("name");
                    QString name = stream.attributes().value("name").toString();
                    //oraLayersNameList.append(stream.attributes().value("name").toString());
                    oraLayersNameList.append(name);
                    QString pngPath = stream.attributes().value("src").toString();
                    QByteArray pngByteArray = zipReader.fileData(pngPath);
                    QPixmap pixmap;
                    pixmap.loadFromData(pngByteArray, "PNG");
                    //pixmap.save("C:/1/" + name + ".png");
                    oraPixmapsList.append(pixmap);
            }

        stream.readNextStartElement();
    }
    zipReader.close();
}
/*
void OpenRaster::readPixmap(const QString oraPath, const QString layerName)
{
}
*/



