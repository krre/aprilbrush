#include "Core.h"
#include <QtGui>

bool Core::isFileExists(const QString& filePath) {
    QFileInfo fi(filePath);
    return fi.exists() && fi.isFile();
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
