#include "Settings.h"

void Settings::setApplicationLanguage(const QString& lang) {
    setValue("Application/language", lang);
}

QString Settings::applicationLanguage() const {
    return value("Application/language").toString();
}

void Settings::setMainWindowGeometry(const QByteArray& geometry) {
    setValue("MainWindow/geometry", geometry);
}

QByteArray Settings::mainWindowGeometry() const {
    return value("MainWindow/geometry").toByteArray();
}

void Settings::setMainWindowState(const QByteArray& state) {
    setValue("MainWindow/state", state);
}

QByteArray Settings::mainWindowState() const {
    return value("MainWindow/state").toByteArray();
}

void Settings::setNewImageSize(const QSize& size) {
    setValue("NewImage/size", size);
}

QSize Settings::newImageSize() const {
    return value("NewImage/size").toSize();
}

void Settings::setColorPickerColor(const QColor& color) {
    setValue("ColorPicker/color", color);
}

QColor Settings::colorPickerColor() const {
    return value("ColorPicker/color", QColor(Qt::red)).value<QColor>();
}
