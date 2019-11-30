#pragma once
#include <QDialog>

class QComboBox;

class Options : public QDialog {
    Q_OBJECT
public:
    Options(QWidget* parent = nullptr);

public slots:
    void accept() override;

private:
    void readSettings();
    bool writeSettings();

    QComboBox* m_languageComboBox = nullptr;
};
