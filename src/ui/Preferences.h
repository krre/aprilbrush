#pragma once
#include "StandardDialog.h"

class QComboBox;

class Preferences : public StandardDialog {
    Q_OBJECT
public:
    Preferences(QWidget* parent = nullptr);

public slots:
    void accept() override;

private:
    void readSettings();
    bool writeSettings();

    QComboBox* m_languageComboBox = nullptr;
};
