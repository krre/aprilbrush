#include "TestSettings.h"
#include <ui/dialog/Preferences.h>
#include <settings/Settings.h>
#include <QTest>
#include <QComboBox>

constexpr auto Language = "ru";

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
    QCOMPARE(preferences.m_languageComboBox->currentData(), Language);
}

void TestPreferences::setPreferences() {
    TestSettings settings;

    // To prevent opening `Restart requred` dialog
    settings.setApplicationLanguage(Language);

    Preferences preferences(&settings);
    preferences.m_languageComboBox->setCurrentIndex(preferences.m_languageComboBox->findData(Language));

    preferences.accept();

    QCOMPARE(settings.applicationLanguage(), Language);
}

QTEST_MAIN(TestPreferences)

#include "TestPreferences.moc"
