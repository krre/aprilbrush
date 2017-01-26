#include "Settings.h"

Settings::Settings(const QString& filePath) {
    settings = new QSettings(filePath, QSettings::IniFormat, this);
    settings->setIniCodec("UTF-8");
}

void Settings::setValue(const QString& group, const QString& key, const QVariant& value) {
    settings->beginGroup(group);
    settings->setValue(key, value);
    settings->endGroup();
}

QVariant Settings::value(const QString& group, const QString& key, const QVariant& defaultValue) {
    return settings->value(QString("%1/%2").arg(group).arg(key), defaultValue);
}

void Settings::setMap(const QString& group, const QVariantMap& map) {
    settings->beginGroup(group);
    QMapIterator<QString, QVariant> i(map);
    while (i.hasNext()) {
        i.next();
        settings->setValue(i.key(), i.value());
    }
    settings->endGroup();
}

QVariantMap Settings::map(const QString& group) {
    settings->beginGroup(group);
    QVariantMap map;
    QStringListIterator i(settings->allKeys());
    while (i.hasNext()) {
        QString key = i.next();
        map[key] = settings->value(key);
    }
    settings->endGroup();
    return map;
}

void Settings::setList(const QString& group, const QStringList& list) {
    settings->remove(group);

    settings->beginGroup(group);
        for (int i = 0; i < list.count(); i++) {
            settings->setValue(QString::number(i), list.at(i));
        }
        settings->endGroup();
}

QStringList Settings::list(const QString& group) {
    settings->beginGroup(group);
        QStringList keys = settings->allKeys();
        QStringList list;
        for (int i = 0; i < keys.count(); i++) {
            list.append(settings->value(keys.at(i)).toString());
        }
    settings->endGroup();

    return list;
}
