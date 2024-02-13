#pragma once
#include <QWidget>

class BrushEngine;
class QSpinBox;

class BrushSlider : public QWidget {
    Q_OBJECT
public:
    BrushSlider(int minValue, int maxValue, int defaultValue);
    int value() const;

signals:
    void valueChanged(int value);

private:
    QSpinBox* m_spinBox = nullptr;
};
