#include "brushsettings.h"

BrushSettings::BrushSettings(BrushEngine *brush)
{
    setWindowTitle(tr("Brush Settings"));
    setWindowFlags(Qt::WindowStaysOnTopHint | Qt::Tool);
    resize(400, -1);

    int resetButtonWidth = 30;
    QGridLayout *gridLayout = new QGridLayout;

    // Size
    QLabel *sizeLabel = new QLabel(tr("Size"));
    sizeSlider = new QSlider(Qt::Horizontal);
    sizeSlider->setRange(sizeValues[minValue], sizeValues[maxValue]);
    sizeSlider->setValue(sizeValues[defaultValue]);
    QSpinBox *sizeSpinBox = new QSpinBox();
    sizeSpinBox->setMaximum(sizeValues[maxValue]);
    sizeSpinBox->setValue(sizeValues[defaultValue]);
    QPushButton *sizeButton = new QPushButton(tr("R"));
    sizeButton->setMaximumWidth(resetButtonWidth);
    QLabel *sizeMeasure = new QLabel(tr("px"));
    connect(sizeSlider, SIGNAL(valueChanged(int)), sizeSpinBox, SLOT(setValue(int)));
    connect(sizeSpinBox, SIGNAL(valueChanged(int)), sizeSlider, SLOT(setValue(int)));
    connect(sizeSlider, SIGNAL(valueChanged(int)), brush, SLOT(setSizeBrush(int)));
    connect(sizeButton, SIGNAL(clicked()), this, SLOT(resetSizeSlider()));

    gridLayout->addWidget(sizeLabel, 0, 0);
    gridLayout->addWidget(sizeSlider, 0, 1);
    gridLayout->addWidget(sizeSpinBox, 0, 2);
    gridLayout->addWidget(sizeMeasure, 0, 3);
    gridLayout->addWidget(sizeButton, 0, 4);

    // Opacity
    QLabel *opacityLabel = new QLabel(tr("Opacity"));
    opacitySlider = new QSlider(Qt::Horizontal);
    opacitySlider->setRange(opacityValues[minValue], opacityValues[maxValue]);
    opacitySlider->setValue(opacityValues[defaultValue]);
    QSpinBox *opacitySpinBox = new QSpinBox();
    opacitySpinBox->setMaximum(opacityValues[maxValue]);
    opacitySpinBox->setValue(opacityValues[defaultValue]);
    QPushButton *opacityButton = new QPushButton(tr("R"));
    opacityButton->setMaximumWidth(resetButtonWidth);
    QLabel *opacityMeasure = new QLabel(tr("%"));
    connect(opacitySlider, SIGNAL(valueChanged(int)), opacitySpinBox, SLOT(setValue(int)));
    connect(opacitySpinBox, SIGNAL(valueChanged(int)), opacitySlider, SLOT(setValue(int)));
    connect(opacitySlider, SIGNAL(valueChanged(int)), brush, SLOT(setAlpha(int)));
    connect(opacityButton, SIGNAL(clicked()), this, SLOT(resetOpacitySlider()));

    gridLayout->addWidget(opacityLabel, 1, 0);
    gridLayout->addWidget(opacitySlider, 1, 1);
    gridLayout->addWidget(opacitySpinBox, 1, 2);
    gridLayout->addWidget(opacityMeasure, 1, 3);
    gridLayout->addWidget(opacityButton, 1, 4);

    setLayout(gridLayout);
}

void BrushSettings::resetSizeSlider()
{
    sizeSlider->setValue(sizeValues[defaultValue]);
}

void BrushSettings::resetOpacitySlider()
{
    opacitySlider->setValue(opacityValues[defaultValue]);
}
