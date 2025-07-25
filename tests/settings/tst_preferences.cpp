#include <ui/dialog/Preferences.h>
#include <settings/Settings.h>
#include <QTest>
#include <QComboBox>

constexpr auto Language = "ru";

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
    void readPreferences();
    void setPreferences();
};

void TestPreferences::readPreferences() {
    TestSettings settings;
    settings.setApplicationLanguage(Language);

    Preferences preferences(&settings);

    QTest::keyClick(&preferences, Qt::Key_Tab); // OK button
    QTest::keyClick(&preferences, Qt::Key_Tab); // Cancel button
    QTest::keyClick(&preferences, Qt::Key_Tab);
    auto languageComboBox = static_cast<QComboBox*>(preferences.focusWidget());

    QCOMPARE(languageComboBox->currentData(), Language);
}

void TestPreferences::setPreferences() {
    TestSettings settings;

    // To prevent opening `Restart requred` dialog
    settings.setApplicationLanguage(Language);

    Preferences preferences(&settings);

    QTest::keyClick(&preferences, Qt::Key_Tab); // OK button
    QTest::keyClick(&preferences, Qt::Key_Tab); // Cancel button
    QTest::keyClick(&preferences, Qt::Key_Tab);
    auto languageComboBox = static_cast<QComboBox*>(preferences.focusWidget());
    languageComboBox->setCurrentIndex(languageComboBox->findData(Language));

    preferences.accept();

    QCOMPARE(settings.applicationLanguage(), Language);
}

QTEST_MAIN(TestPreferences)

#include "tst_preferences.moc"
