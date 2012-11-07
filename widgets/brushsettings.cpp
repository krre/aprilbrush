#include "brushsettings.h"

BrushSettings::BrushSettings(BrushEngine *brush)
{
    setWindowTitle(tr("Brush Settings"));
    setWindowFlags(Qt::WindowStaysOnTopHint | Qt::Tool);
    resize(400, -1);

    QGridLayout *gridLayout = new QGridLayout;

    addSlider(brush, gridLayout, tr("Size"), 1, 20, 150, SLOT(setSizeBrush(int)), 0);
    addSlider(brush, gridLayout, tr("Opacity"), 0, 50, 100, SLOT(setAlpha(int)), 1);
    addSlider(brush, gridLayout, tr("Space"), 1, 25, 500, SLOT(setSpaceBrush(int)), 3);

    setLayout(gridLayout);
}

void BrushSettings::resetSlider(QSlider *slider, int defaultValue)
{
    slider->setValue(defaultValue);
}

void BrushSettings::addSlider(BrushEngine *brush, QGridLayout *layout, QString name,
                                 int minValue, int defaultValue, int maxValue, const char *slot, int row)
{
    QLabel *label = new QLabel(name);
    layout->addWidget(label, row, 0);

    QSlider *slider = new QSlider(Qt::Horizontal);
    slider->setRange(minValue, maxValue);
    slider->setValue(defaultValue);
    layout->addWidget(slider, row, 1);

    QSpinBox *spinBox = new QSpinBox();
    spinBox->setMaximum(maxValue);
    spinBox->setValue(defaultValue);
    layout->addWidget(spinBox, row, 3);

    QPushButton *button = new QPushButton(tr("R"));
    button->setMaximumWidth(30);
    layout->addWidget(button, row, 4);

    connect(slider, SIGNAL(valueChanged(int)), spinBox, SLOT(setValue(int)));
    connect(slider, SIGNAL(valueChanged(int)), brush, slot);
    connect(spinBox, SIGNAL(valueChanged(int)), slider, SLOT(setValue(int)));

    //connect(button, SIGNAL(clicked()), this, SLOT(resetSlider()));
}
