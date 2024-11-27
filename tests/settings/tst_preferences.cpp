#include <settings/Settings.h>
#include <QTest>

class TestSettings : public Settings {

public:
    void setApplication(const Application& application) override {}
    Application application() const override {}

    void setMainWindow(const MainWindow& mainWindow) override {}
    MainWindow mainWindow() const override {}

    void setNewImage(const NewImage& newImage) override {}
    NewImage newImage() const override {}

    void setColorPicker(const ColorPicker& colorPicker) override {}
    ColorPicker colorPicker() const override {}

    void setInputDevice(const InputDevice& inputDevice) override {}
    InputDevice inputDevice() const override {}
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
