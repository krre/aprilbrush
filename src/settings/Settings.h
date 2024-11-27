#pragma once
#include <QVariant>
#include <QSize>
#include <QColor>

class Settings {
public:
    struct InputDevice {
        QByteArray geometry;
    };

    void setApplicationLanguage(const QString& lang);
    QString applicationLanguage() const;

    void setMainWindowGeometry(const  QByteArray& geometry);
    QByteArray mainWindowGeometry() const;

    void setMainWindowState(const  QByteArray& state);
    QByteArray mainWindowState() const;

    void setNewImageSize(const QSize& size);
    QSize newImageSize() const;

    void setColorPickerColor(const QColor& color);
    QColor colorPickerColor() const;

    virtual void setInputDevice(const InputDevice& inputDevice) = 0;
    virtual InputDevice inputDevice() const = 0;

protected:
    virtual void setValue(const QString& key, const QVariant& value) = 0;
    virtual QVariant value(const QString& key, const QVariant& defaultValue = QVariant()) const = 0;
};
