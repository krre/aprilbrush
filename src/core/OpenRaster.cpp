#include "OpenRaster.h"
#include "engine/Layer.h"
#include <QtCore/private/qzipwriter_p.h>
#include <QtCore/private/qzipreader_p.h>
#include <QtGui>

void OpenRaster::write(const QString& filePath, const QSize& size, const Layers& layers) {
    QZipWriter zipWriter(filePath);
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
    stream.writeAttribute("w", QString::number(size.width()));
    stream.writeAttribute("h",QString::number(size.height()));
    stream.writeStartElement("stack");

    for (const auto& layer : layers) {
        QString src = "data/" + layer.name() + ".png";

        QByteArray data;
        QBuffer buffer(&data);
        buffer.open(QIODevice::WriteOnly);
        layer.refPixmap().save(&buffer, "PNG");
        buffer.close();
        zipWriter.addFile(src, data);

        // layer
        stream.writeStartElement("layer");
        stream.writeAttribute("name", layer.name());
        stream.writeAttribute("composite-op", "svg:src-over");
        stream.writeAttribute("visibility", layer.isVisible() ? "visible" : "hidden");
        stream.writeAttribute("edit-locked", QVariant(layer.isLocked()).toString());
        stream.writeAttribute("selected", QVariant(layer.isSelected()).toString());
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

Layers OpenRaster::read(const QString& filePath) {
    QZipReader zipReader(filePath, QIODevice::ReadOnly);

    QByteArray xmlByteArray = zipReader.fileData("stack.xml");
    QXmlStreamReader stream(xmlByteArray);
    Layers result;

    while (!stream.atEnd()) {
        if (stream.isStartElement()) {
            if (stream.name().toString() == "layer") {
                QString name = stream.attributes().value("name").toString();

                QByteArray data = zipReader.fileData(stream.attributes().value("src").toString());
                QPixmap pixmap;
                pixmap.loadFromData(data, "PNG");

                Layer layer(name, pixmap);

                layer.setVisible(QVariant(stream.attributes().value("visibility").toString()).toBool());
                layer.setLocked(QVariant(stream.attributes().value("edit-locked").toString()).toBool());
                layer.setSelected(QVariant(stream.attributes().value("selected").toString()).toBool());

                result.append(std::move(layer));
            }
        }

        stream.readNextStartElement();
    }

    zipReader.close();

    return result;
}
