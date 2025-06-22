#pragma once
#include "StandardDialog.h"

class Settings;

class QLineEdit;
class QSpinBox;

class NewImage : public StandardDialog {
    Q_OBJECT
public:
    explicit NewImage(const QString& name, Settings* settings);

    QString name() const;
    QSize size() const;

private slots:
    void accept() override;
    void resetSize();
    void onNameChanged(const QString& text);

private:
    void readSettings();
    void writeSettings();

    void setupSpinBox(QSpinBox* spinBox);

    Settings* m_settings = nullptr;

    QLineEdit* m_nameEdit = nullptr;
    QSpinBox* m_widthSpinBox = nullptr;
    QSpinBox* m_heightSpinBox = nullptr;
};
