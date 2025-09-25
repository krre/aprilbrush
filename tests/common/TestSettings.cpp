#include "TestSettings.h"

void TestSettings::setValue(const QString &key, const QVariant &value) {
    settings[key] = value;
}

QVariant TestSettings::value(const QString &key, const QVariant &defaultValue) const {
    return settings.contains(key) ? settings[key] : defaultValue;
}
