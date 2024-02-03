#pragma once
#include "Settings.h"

class FileSettings : public Settings {
public:
    FileSettings();

    void setGeneral(const General& general) override;
    General general() const override;

    void setMainWindow(const MainWindow& mainWindow) override;
    MainWindow mainWindow() const override;
    bool containsGeometry() const override;

    void setNewImage(const NewImage& newImage) override;
    NewImage newImage() const override;
};
