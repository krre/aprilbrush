#include "FileSettings.h"
#include <QSettings>

FileSettings::FileSettings() {}

void FileSettings::setGeneral(const General& general) {
    QSettings settings;
    settings.beginGroup("General");
    settings.setValue("language", general.language);
    settings.endGroup();
}

Settings::General FileSettings::general() const {
    General result;

    QSettings settings;
    settings.beginGroup("General");
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
