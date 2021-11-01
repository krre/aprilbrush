#pragma once
#include "Dialog.h"

class QSpinBox;

class NewImage : public Dialog {
    Q_OBJECT
public:
    explicit NewImage(QWidget* parent = nullptr);

    QSize imageSize() const;

private slots:
    void accept() override;
    void resetSize();

private:
    void readSettings();
    void writeSettings();

    void setupSpinBox(QSpinBox* spinBox);

    QSpinBox* m_widthSpinBox;
    QSpinBox* m_heightSpinBox;
};
