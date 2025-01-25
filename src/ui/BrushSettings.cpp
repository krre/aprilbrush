#include "BrushSettings.h"
#include "BrushSlider.h"
#include "engine/BrushEngine.h"
#include <QFormLayout>

BrushSettings::BrushSettings(BrushEngine* brushEngine) : m_brushEngine(brushEngine) {
    setWindowTitle(tr("Brush Settings"));

    auto sizeSlider = new BrushSlider(1, 150, 40);
    connect(sizeSlider, &BrushSlider::valueChanged, m_brushEngine, &BrushEngine::setSize);
    m_brushEngine->setSize(sizeSlider->value());

    auto opacitySlider = new BrushSlider(0, 100, 50);
    connect(opacitySlider, &BrushSlider::valueChanged, m_brushEngine, &BrushEngine::setOpacity);
    m_brushEngine->setOpacity(opacitySlider->value());

    auto spacingSlider = new BrushSlider(5, 200, 100);
    connect(spacingSlider, &BrushSlider::valueChanged, m_brushEngine, &BrushEngine::setSpacing);
    m_brushEngine->setSpacing(spacingSlider->value());

    auto hardnessSlider = new BrushSlider(0, 100, 80);
    connect(hardnessSlider, &BrushSlider::valueChanged, m_brushEngine, &BrushEngine::setHardness);
    m_brushEngine->setHardness(hardnessSlider->value());

    auto flowSlider = new BrushSlider(0, 100, 30);
    connect(flowSlider, &BrushSlider::valueChanged, m_brushEngine, &BrushEngine::setFlow);
    m_brushEngine->setFlow(flowSlider->value());

    auto roundnessSlider = new BrushSlider(1, 100, 100);
    connect(roundnessSlider, &BrushSlider::valueChanged, m_brushEngine, &BrushEngine::setRoundness);
    m_brushEngine->setRoundness(roundnessSlider->value());

    auto angleSlider = new BrushSlider(1, 180, 0);
    connect(angleSlider, &BrushSlider::valueChanged, m_brushEngine, &BrushEngine::setAngle);
    m_brushEngine->setAngle(angleSlider->value());

    auto jitterSlider = new BrushSlider(0, 500, 0);
    connect(jitterSlider, &BrushSlider::valueChanged, m_brushEngine, &BrushEngine::setJitter);
    m_brushEngine->setJitter(jitterSlider->value());

    auto eraserSlider = new BrushSlider(0, 100, 0);
    connect(eraserSlider, &BrushSlider::valueChanged, m_brushEngine, &BrushEngine::setEraser);
    m_brushEngine->setEraser(eraserSlider->value());

    auto formLayout = new QFormLayout;
    formLayout->addRow(tr("Size:"), sizeSlider);
    formLayout->addRow(tr("Opacity:"), opacitySlider);
    formLayout->addRow(tr("Spacing:"), spacingSlider);
    formLayout->addRow(tr("Hardness:"), hardnessSlider);
    formLayout->addRow(tr("Flow:"), flowSlider);
    formLayout->addRow(tr("Roundness:"), roundnessSlider);
    formLayout->addRow(tr("Angle:"), angleSlider);
    formLayout->addRow(tr("Jitter:"), jitterSlider);
    formLayout->addRow(tr("Eraser:"), eraserSlider);

    setLayout(formLayout);
}
