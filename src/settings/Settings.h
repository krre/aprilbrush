#pragma once
#include <QVariant>
#include <QSize>
#include <QColor>

class Settings {
public:
    struct NewImage {
        QSize size;
    };

    struct ColorPicker {
        QColor color;
    };

    struct InputDevice {
        QByteArray geometry;
    };

    void setApplicationLanguage(const QString& lang);
    QString applicationLanguage() const;

    void setMainWindowGeometry(const  QByteArray& geometry);
    QByteArray mainWindowGeometry() const;

    void setMainWindowState(const  QByteArray& state);
    QByteArray mainWindowState() const;

    virtual void setNewImage(const NewImage& newImage) = 0;
    virtual NewImage newImage() const = 0;

    virtual void setColorPicker(const ColorPicker& colorPicker) = 0;
    virtual ColorPicker colorPicker() const = 0;

    virtual void setInputDevice(const InputDevice& inputDevice) = 0;
    virtual InputDevice inputDevice() const = 0;

protected:
    virtual void setValue(const QString& key, const QVariant& value) = 0;
    virtual QVariant value(const QString& key, const QVariant& defaultValue = QVariant()) const = 0;
};
