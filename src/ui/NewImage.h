#pragma once
#include <QDialog>

class QSpinBox;

class NewImage : public QDialog {
    Q_OBJECT
public:
    explicit NewImage(QWidget* parent = nullptr);

    QSize imageSize() const;

private slots:
    void accept() override;
    void resetToScreenSize();

private:
    void readSettings();
    void writeSettings();

    void setupSpinBox(QSpinBox* spinBox);

    QSpinBox* m_widthSpinBox;
    QSpinBox* m_heightSpinBox;
};
