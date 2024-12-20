#include <settings/Settings.h>
#include <QTest>

class TestSettings : public Settings {

protected:
    void setValue(const QString& key, const QVariant& value) override {
        settings[key] = value;
    }

    QVariant value(const QString& key, const QVariant& defaultValue = QVariant()) const override {
        return settings.contains(key) ? settings[key] : defaultValue;
    }

private:
    QHash<QString, QVariant> settings;
};

class TestPreferences : public QObject {
    Q_OBJECT
private slots:
    void readOptions();
    void setOptions();
};

void TestPreferences::readOptions() {
    TestSettings settings;
}

void TestPreferences::setOptions() {
    TestSettings settings;
}

QTEST_MAIN(TestPreferences)

#include "tst_preferences.moc"
