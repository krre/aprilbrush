#include "Settings.h"
#include <QtCore>

Settings::Settings(const QString& filePath) {
    _settings = new QSettings(filePath, QSettings::IniFormat, this);
    _settings->setIniCodec("UTF-8");
}

void Settings::setValue(const QString& group, const QString& key, const QVariant& value) {
    _settings->beginGroup(group);
    _settings->setValue(key, value);
    _settings->endGroup();
}

QVariant Settings::value(const QString& group, const QString& key, const QVariant& defaultValue) {
    return _settings->value(QString("%1/%2").arg(group).arg(key), defaultValue);
}

void Settings::setMap(const QString& group, const QVariantMap& map) {
    _settings->beginGroup(group);
    QMapIterator<QString, QVariant> i(map);
    while (i.hasNext()) {
        i.next();
        _settings->setValue(i.key(), i.value());
    }
    _settings->endGroup();
}

QVariantMap Settings::map(const QString& group) {
    _settings->beginGroup(group);
    QVariantMap map;
    QStringListIterator i(_settings->allKeys());
    while (i.hasNext()) {
        QString key = i.next();
        map[key] = _settings->value(key);
    }
    _settings->endGroup();
    return map;
}

void Settings::setList(const QString& group, const QStringList& list) {
    _settings->remove(group);

    _settings->beginGroup(group);
        for (int i = 0; i < list.count(); i++) {
            _settings->setValue(QString::number(i), list.at(i));
        }
        _settings->endGroup();
}

QStringList Settings::list(const QString& group) {
    _settings->beginGroup(group);
        QStringList keys = _settings->allKeys();
        QStringList list;
        for (int i = 0; i < keys.count(); i++) {
            list.append(_settings->value(keys.at(i)).toString());
        }
    _settings->endGroup();

    return list;
}
