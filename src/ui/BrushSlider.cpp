#include "BrushSlider.h"
#include <QSlider>
#include <QSpinBox>
#include <QHBoxLayout>

BrushSlider::BrushSlider(int minValue, int maxValue, int defaultValue) {
    auto slider = new QSlider(Qt::Horizontal);
    slider->setRange(minValue, maxValue);

    m_spinBox = new QSpinBox();
    m_spinBox->setRange(minValue, maxValue);

    connect(slider, &QSlider::valueChanged, m_spinBox, &QSpinBox::setValue);
    connect(slider, &QSlider::valueChanged, this, &BrushSlider::valueChanged);
    connect(m_spinBox, &QSpinBox::valueChanged, slider, &QSlider::setValue);

    m_spinBox->setValue(defaultValue);

    auto layout = new QHBoxLayout;
    layout->setContentsMargins(QMargins());
    layout->addWidget(slider);
    layout->addWidget(m_spinBox);

    setLayout(layout);
}

int BrushSlider::value() const {
    return m_spinBox->value();
}
