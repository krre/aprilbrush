#include "BrushSettings.h"
#include <engine/BrushEngine.h>
#include <QtWidgets>

BrushSettings::BrushSettings(BrushEngine* brushEngine) : m_brushEngine(brushEngine) {
    setWindowTitle(tr("Brush Settings"));

    auto formLayout = new QFormLayout;
    formLayout->addRow(tr("Size:"), createSlider(1, 150, 40, [=] (int size) { m_brushEngine->setSize(size); }));
    formLayout->addRow(tr("Opacity:"), createSlider(0, 100, 50, [=] (int opacity) { m_brushEngine->setOpacity(opacity); }));
    formLayout->addRow(tr("Spacing:"), createSlider(5, 25, 100, [=] (int spacing) { m_brushEngine->setSpacing(spacing); }));
    formLayout->addRow(tr("Hardness:"), createSlider(0, 100, 80, [=] (int hardness) { m_brushEngine->setHardness(hardness); }));
    formLayout->addRow(tr("Flow:"), createSlider(0, 100, 30, [=] (int flow) { m_brushEngine->setFlow(flow); }));
    formLayout->addRow(tr("Roundness:"), createSlider(1, 100, 100, [=] (int roundness) { m_brushEngine->setRoundness(roundness); }));
    formLayout->addRow(tr("Angle:"), createSlider(1, 180, 0, [=] (int angle) { m_brushEngine->setAngle(angle); }));
    formLayout->addRow(tr("Jitter:"), createSlider(0, 500, 0, [=] (int jitter) { m_brushEngine->setJitter(jitter); }));
    formLayout->addRow(tr("Eraser:"), createSlider(0, 100, 0, [=] (int eraser) { m_brushEngine->setEraser(eraser); }));

    setLayout(formLayout);
}

QLayout* BrushSettings::createSlider(int minValue, int maxValue, int defaultValue, const std::function<void (int)>& brushSlot) {
    auto slider = new QSlider(Qt::Horizontal);
    slider->setRange(minValue, maxValue);
    slider->setValue(defaultValue);

    auto spinBox = new QSpinBox();
    spinBox->setMaximum(maxValue);
    spinBox->setValue(defaultValue);
    brushSlot(defaultValue);

    connect(slider, &QSlider::valueChanged, spinBox, &QSpinBox::setValue);
    connect(slider, &QSlider::valueChanged, [=] (int value) { brushSlot(value); });
    connect(spinBox, &QSpinBox::valueChanged, slider, &QSlider::setValue);

    auto layout = new QHBoxLayout;
    layout->addWidget(slider);
    layout->addWidget(spinBox);

    return layout;
}
