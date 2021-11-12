#include "Core.h"
#include <QtGui>

bool Core::isFileExists(const QString& filePath) {
    QFileInfo fi(filePath);
    return fi.exists() && fi.isFile();
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
