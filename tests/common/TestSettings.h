#include <settings/Settings.h>

class TestSettings : public Settings {

protected:
    void setValue(const QString& key, const QVariant& value) override;
    QVariant value(const QString& key, const QVariant& defaultValue = QVariant()) const override;

private:
    QHash<QString, QVariant> settings;
};
