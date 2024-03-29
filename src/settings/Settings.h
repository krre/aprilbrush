#pragma once
#include <QByteArray>
#include <QString>
#include <QSize>
#include <QColor>

class Settings {
public:
    struct General {
        QString language;
    };

    struct MainWindow {
        QByteArray geometry;
        QByteArray state;
    };

    struct NewImage {
        QSize size;
    };

    struct ColorPicker {
        QColor color;
    };

    virtual void setGeneral(const General& general) = 0;
    virtual General general() const = 0;

    virtual void setMainWindow(const MainWindow& mainWindow) = 0;
    virtual MainWindow mainWindow() const = 0;

    virtual void setNewImage(const NewImage& newImage) = 0;
    virtual NewImage newImage() const = 0;

    virtual void setColorPicker(const ColorPicker& colorPicker) = 0;
    virtual ColorPicker colorPicker() const = 0;
};
