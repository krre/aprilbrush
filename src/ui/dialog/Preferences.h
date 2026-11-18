#pragma once
#include "StandardDialog.h"

class Settings;

class QComboBox;

class Preferences : public StandardDialog {
    Q_OBJECT
    friend class TestPreferences;
public:
    Preferences(Settings* settings);

public slots:
    void accept() override;

private:
    void readSettings();
    bool writeSettings();

    Settings* m_settings = nullptr;

    QComboBox* m_languageComboBox = nullptr;
};
