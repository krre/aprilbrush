#pragma once
#include "StandardDialog.h"

class Settings;

class QComboBox;

class Preferences : public StandardDialog {
    Q_OBJECT
public:
    Preferences(Settings* settings, QWidget* parent = nullptr);

public slots:
    void accept() override;

private:
    void readSettings();
    bool writeSettings();

    Settings* m_settings = nullptr;

    QComboBox* m_languageComboBox = nullptr;
};
