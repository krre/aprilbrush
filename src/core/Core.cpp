#include "Core.h"
#include <QtGui/private/qzipwriter_p.h>
#include <QtGui/private/qzipreader_p.h>
#include <QtGui>

bool Core::isFileExists(const QString& filePath) {
    QFileInfo fi(filePath);
    return fi.exists() && fi.isFile();
}

void Core::writeOra(const QString& oraPath, const QSize& canvasSize, const QVariantList& layerList) {
//    QZipWriter zipWriter(oraPath);
//    zipWriter.setCompressionPolicy(QZipWriter::AutoCompress);

//    QByteArray xmlByteArray;

//    // mimetype file
//    xmlByteArray.append("image/openraster");
//    zipWriter.addFile("mimetype", xmlByteArray);

//    // stack.xml file
//    QXmlStreamWriter stream(&xmlByteArray);
//    stream.setAutoFormatting(true);

//    stream.writeStartDocument();

//    stream.writeStartElement("image");
//    stream.writeAttribute("w", QString::number(canvasSize.width()));
//    stream.writeAttribute("h",QString::number(canvasSize.height()));
//    stream.writeStartElement("stack");

//    QByteArray ba;
//    QBuffer buffer(&ba);

//    for (int i = 0; i < layerList.count(); i++) {
//        QMap<QString, QVariant> map = layerList.at(i).toMap();
//        QString name = map.value("name").toString();
//        QString isVisible = map.value("isVisible").toString();
//        QString isLock = map.value("isLock").toString();
//        QString isSelected = map.value("isSelected").toString();

//        buffer.open(QIODevice::WriteOnly);
//        auto obj = qvariant_cast<QObject*>(map.value("canvasItem"));
//        auto layer = qobject_cast<Layer*>(obj);
//        QPixmap* pixmap = layer->pixmap();
//        pixmap->save(&buffer, "PNG");
//        buffer.close();

//        QString src = "data/" + name + ".png";
//        zipWriter.addFile(src, ba);

//        // layer
//        stream.writeStartElement("layer");
//        stream.writeAttribute("name", name);
//        stream.writeAttribute("composite-op", "svg:src-over");
//        stream.writeAttribute("visibility", isVisible == "true" ? "visible" : "hidden");
//        stream.writeAttribute("edit-locked", isLock);
//        stream.writeAttribute("selected", isSelected);
//        stream.writeAttribute("src", src);
//        stream.writeAttribute("x", "0");
//        stream.writeAttribute("y", "0");
//        stream.writeAttribute("opacity", "1.0");
//        stream.writeEndElement(); // layer
//    }

//    stream.writeEndElement(); // stack
//    stream.writeEndElement(); // image
//    stream.writeEndDocument(); // document
//    zipWriter.addFile("stack.xml", xmlByteArray);

//    zipWriter.close();
}

QVariantList Core::readOra(const QString& oraPath) {
    QZipReader zipReader(oraPath, QIODevice::ReadOnly);

    QByteArray xmlByteArray = zipReader.fileData("stack.xml");
    QXmlStreamReader stream(xmlByteArray);
    QVariantMap map;
    QVariantList list;

    while (!stream.atEnd()) {
        if (stream.isStartElement()) {
            if (stream.name().toString() == "layer") {
                for (int i = 0; i < stream.attributes().size(); i++) {
                    map[stream.attributes().at(i).name().toString()] = stream.attributes().at(i).value().toString();
                }
                QByteArray ba = zipReader.fileData(stream.attributes().value("src").toString());
                map["image"] = QString(ba.toBase64());
                list.append(map);
                map.clear();
            }
        }
        stream.readNextStartElement();
    }
    zipReader.close();

    return list;
}

QVariantMap Core::readOraAttr(const QString& oraPath) {
    QVariantMap map;

    QZipReader zipReader(oraPath, QIODevice::ReadOnly);

    QByteArray xmlByteArray = zipReader.fileData("stack.xml");
    QXmlStreamReader stream(xmlByteArray);

    while (!stream.atEnd()) {
        if (stream.isStartElement()) {
            if (stream.name().toString() == "image") {
                for (int i = 0; i < stream.attributes().size(); i++) {
                    map[stream.attributes().at(i).name().toString()] = stream.attributes().at(i).value().toString();
                }
            }
        }
        stream.readNextStartElement();
    }
    zipReader.close();

    return map;
}

void Core::writePng(const QString& pngPath, const QVariantList& canvasItems) {
//    QPixmap pixmap;
//    for (int i = canvasItems.count() - 1; i >= 0; i--) {
//        auto obj = qvariant_cast<QObject*>(canvasItems.at(i));
//        auto layer = qobject_cast<Layer*>(obj);
//        QPixmap* canvasPixmap = layer->pixmap();
//        if (pixmap.isNull()) {
//            pixmap = QPixmap(canvasPixmap->width(), canvasPixmap->height());
//            pixmap.fill(Qt::white);
//        }
//        QPainter painter(&pixmap);
//        painter.drawPixmap(0, 0, *canvasPixmap);
//    }
//    pixmap.save(pngPath);
}

void Core::setCursorShape(const QString& type, int size) {
    if (type == "paint") {
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
    }
}

QString Core::pathToBaseName(const QString& path) {
    QFileInfo fileInfo(path);
    return fileInfo.baseName();
}

QString Core::pathToFileName(const QString& path) {
    QFileInfo fileInfo(path);
    return fileInfo.fileName();
}

QColor Core::hsvToColor(qreal h, qreal s, qreal v) {
    QColor color;
    color.setHsvF(h, s, v);
    return color;
}

QColor Core::pickColor(const QPointF& point, const QVariantList& canvasItems) {
    QPixmap pixmap;
//    for (int i = canvasItems.count() - 1; i >= 0; i--) {
//        auto obj = qvariant_cast<QObject*>(canvasItems.at(i));
//        auto layer = qobject_cast<Layer*>(obj);
//        QPixmap* canvasPixmap = layer->pixmap();
//        if (pixmap.isNull()) {
//            pixmap = QPixmap(canvasPixmap->width(), canvasPixmap->height());
//            pixmap.fill(Qt::white);
//        }
//        QPainter painter(&pixmap);
//        painter.drawPixmap(0, 0, *canvasPixmap);
//    }

    return QColor(pixmap.toImage().pixel(qRound(point.x()), qRound(point.y())));
}

QVariantMap Core::colorToHsv(const QColor& color) {
    QVariantMap map;
    map["h"] = color.hueF();
    map["s"] = color.saturationF();
    map["v"] = color.valueF();
    return map;
}

QString Core::byteArrayToBase64(const QByteArray& value) {
    return value.toBase64();
}

QByteArray Core::base64ToByteArray(const QString& value) {
    return QByteArray::fromBase64(value.toLatin1());
}
