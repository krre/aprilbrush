#pragma once
#include <QVariant>
#include <QSize>
#include <QColor>

class Settings {
public:
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

    void setInputDeviceGeometry(const QByteArray& geometry);
    QByteArray inputDeviceGeometry() const;

protected:
    virtual void setValue(const QString& key, const QVariant& value) = 0;
    virtual QVariant value(const QString& key, const QVariant& defaultValue = QVariant()) const = 0;
};
