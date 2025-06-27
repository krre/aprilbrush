#pragma once
#include "Settings.h"
#include <QObject>

class FileSettings : public QObject, public Settings {
public:
    FileSettings(QObject* parent = nullptr);

protected:
    void setValue(const QString& key, const QVariant& value) override;
    QVariant value(const QString& key, const QVariant& defaultValue = QVariant()) const override;
};
