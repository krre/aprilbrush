#pragma once
#include <QObject>
#include <QUrl>
#include <QVariantMap>
#include <QColor>

class Core {
public:
    Core() = default;
    bool isFileExists(const QString& filePath);
    QString urlToPath(const QUrl& url) { return url.toLocalFile(); }
    QString pathToBaseName(const QString& path);
    QString pathToFileName(const QString& path);
    QColor hsvToColor(qreal h, qreal s, qreal v);
    QVariantMap colorToHsv(const QColor& color);
    QString byteArrayToBase64(const QByteArray& value);
    QByteArray base64ToByteArray(const QString& value);
    QString buildDate() { return QString(__DATE__); }
    QString qtVersion() { return QT_VERSION_STR; }
};
