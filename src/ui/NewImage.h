#pragma once
#include <QDialog>

class QLineEdit;
class QSpinBox;

class NewImage : public QDialog {
    Q_OBJECT
public:
    explicit NewImage(QWidget* parent = nullptr);

private slots:
    void resetToScreenSize();

private:
    QLineEdit* m_nameLineEdit;
    QSpinBox* m_widthSpinBox;
    QSpinBox* m_heightSpinBox;
};
