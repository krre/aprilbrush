#include "openraster.h"

OpenRaster::OpenRaster()
{
}

void OpenRaster::write(const QString oraPath, const QSize imageSize,
                       const QVariantList paintedItemList, const QVariantList layersNameList)
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

    qDebug() << paintedItemList;

    PaintedItem *paintedItem;
    QByteArray pixmapByteArray;
    QBuffer buffer(&pixmapByteArray);

    for (int i = 0; i < paintedItemList.length(); i++)
    {
        QVariant v = paintedItemList.at(i);
        paintedItem = v.value<PaintedItem*>();

        v = layersNameList.at(i);
        QString layerName = v.value<QString>();

        // PNG file
        buffer.open(QIODevice::WriteOnly);
        paintedItem->pixmapItem.save(&buffer, "PNG");
        buffer.close();
        zipWriter.addFile("data/" + layerName + ".png", pixmapByteArray);

        // layer
        stream.writeStartElement("layer");
        stream.writeAttribute("name", layerName);
        stream.writeAttribute("composite-op", "svg:src-over");
        stream.writeAttribute("visibility", "visible");
        stream.writeAttribute("src", "data/" + layerName + ".png");
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
