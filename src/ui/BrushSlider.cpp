#include "BrushSlider.h"
#include <QSlider>
#include <QSpinBox>
#include <QHBoxLayout>

BrushSlider::BrushSlider(int minValue, int maxValue, int defaultValue) {
    auto slider = new QSlider(Qt::Horizontal);
    slider->setRange(minValue, maxValue);

    spinBox = new QSpinBox();
    spinBox->setRange(minValue, maxValue);

    connect(slider, &QSlider::valueChanged, spinBox, &QSpinBox::setValue);
    connect(slider, &QSlider::valueChanged, this, &BrushSlider::valueChanged);
    connect(spinBox, &QSpinBox::valueChanged, slider, &QSlider::setValue);

    spinBox->setValue(defaultValue);

    auto layout = new QHBoxLayout;
    layout->setContentsMargins(QMargins());
    layout->addWidget(slider);
    layout->addWidget(spinBox);

    setLayout(layout);
}

int BrushSlider::value() const {
    return spinBox->value();
}
