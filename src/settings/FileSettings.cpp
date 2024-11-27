#include "FileSettings.h"
#include <QSettings>

FileSettings::FileSettings() {}

void FileSettings::setApplication(const Application& application) {
    QSettings settings;
    settings.beginGroup("Application");
    settings.setValue("language", application.language);
    settings.endGroup();
}

Settings::Application FileSettings::application() const {
    Application result;

    QSettings settings;
    settings.beginGroup("Application");
    result.language = settings.value("language").toString();
    settings.endGroup();

    return result;
}

void FileSettings::setMainWindow(const MainWindow& mainWindow) {
    QSettings settings;
    settings.beginGroup("MainWindow");

    settings.setValue("geometry", mainWindow.geometry);
    settings.setValue("state", mainWindow.state);

    settings.endGroup();
}

Settings::MainWindow FileSettings::mainWindow() const {
    MainWindow result;

    QSettings settings;
    settings.beginGroup("MainWindow");

    result.geometry = settings.value("geometry").toByteArray();
    result.state = settings.value("state").toByteArray();

    settings.endGroup();

    return result;
}

void FileSettings::setNewImage(const NewImage& newImage) {
    QSettings settings;
    settings.beginGroup("NewImage");
    settings.setValue("size", newImage.size);
    settings.endGroup();
}

Settings::NewImage FileSettings::newImage() const {
    NewImage result;

    QSettings settings;
    settings.beginGroup("NewImage");
    result.size = settings.value("size").toSize();
    settings.endGroup();

    return result;
}

void FileSettings::setColorPicker(const ColorPicker& colorPicker) {
    QSettings settings;
    settings.beginGroup("ColorPicker");
    settings.setValue("color", colorPicker.color);
    settings.endGroup();
}

Settings::ColorPicker FileSettings::colorPicker() const {
    ColorPicker result;

    QSettings settings;
    settings.beginGroup("ColorPicker");
    result.color = settings.value("color", QColor(Qt::red)).value<QColor>();
    settings.endGroup();

    return result;
}

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
