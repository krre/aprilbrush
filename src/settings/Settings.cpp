#include "Settings.h"

namespace Application {
    constexpr auto Language = "Application/language";
}

namespace MainWindow {
    constexpr auto Geometry = "MainWindow/geometry";
    constexpr auto State = "MainWindow/state";
}

namespace NewImage {
    constexpr auto Size = "NewImage/size";
}

namespace ColorPicker {
    constexpr auto Color = "Application/color";
}

namespace InputDevice {
    constexpr auto Geometry = "Application/geometry";
}

void Settings::setApplicationLanguage(const QString& lang) {
    setValue(Application::Language, lang);
}

QString Settings::applicationLanguage() const {
    return value(Application::Language).toString();
}

void Settings::setMainWindowGeometry(const QByteArray& geometry) {
    setValue(MainWindow::Geometry, geometry);
}

QByteArray Settings::mainWindowGeometry() const {
    return value(MainWindow::Geometry).toByteArray();
}

void Settings::setMainWindowState(const QByteArray& state) {
    setValue(MainWindow::State, state);
}

QByteArray Settings::mainWindowState() const {
    return value(MainWindow::State).toByteArray();
}

void Settings::setNewImageSize(const QSize& size) {
    setValue(NewImage::Size, size);
}

QSize Settings::newImageSize() const {
    return value(NewImage::Size).toSize();
}

void Settings::setColorPickerColor(const QColor& color) {
    setValue(ColorPicker::Color, color);
}

QColor Settings::colorPickerColor() const {
    return value(ColorPicker::Color, QColor(Qt::red)).value<QColor>();
}

void Settings::setInputDeviceGeometry(const QByteArray& geometry) {
    setValue(InputDevice::Geometry, geometry);
}

QByteArray Settings::inputDeviceGeometry() const {
    return value(InputDevice::Geometry).toByteArray();
}
