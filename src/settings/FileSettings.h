#pragma once
#include "Settings.h"

class FileSettings : public Settings {
public:
    FileSettings();

    void setNewImage(const NewImage& newImage) override;
    NewImage newImage() const override;

    void setColorPicker(const ColorPicker& colorPicker) override;
    ColorPicker colorPicker() const override;

    void setInputDevice(const InputDevice& inputDevice) override;
    InputDevice inputDevice() const override;

protected:
    void setValue(const QString& key, const QVariant& value) override;
    QVariant value(const QString& key, const QVariant& defaultValue = QVariant()) const override;
};
