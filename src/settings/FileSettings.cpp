#include "FileSettings.h"
#include <QSettings>

FileSettings::FileSettings() {}

void FileSettings::setInputDevice(const InputDevice& inputDevice) {
    QSettings settings;
    settings.beginGroup("InputDevice");
    settings.setValue("geometry", inputDevice.geometry);
    settings.endGroup();
}

Settings::InputDevice FileSettings::inputDevice() const {
    InputDevice result;

    QSettings settings;
    settings.beginGroup("InputDevice");
    result.geometry = settings.value("geometry").toByteArray();
    settings.endGroup();

    return result;
}

void FileSettings::setValue(const QString& key, const QVariant& value) {
    QSettings settings;
    settings.setValue(key, value);
}

QVariant FileSettings::value(const QString& key, const QVariant& defaultValue) const {
    QSettings settings;
    return settings.value(key, defaultValue);
}
