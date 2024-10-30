#pragma once
#include "Settings.h"

class FileSettings : public Settings {
public:
    FileSettings();

    void setApplication(const Application& application) override;
    Application application() const override;

    void setMainWindow(const MainWindow& mainWindow) override;
    MainWindow mainWindow() const override;

    void setNewImage(const NewImage& newImage) override;
    NewImage newImage() const override;

    void setColorPicker(const ColorPicker& colorPicker) override;
    ColorPicker colorPicker() const override;
};
