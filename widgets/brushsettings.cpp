#include "brushsettings.h"

BrushSettings::BrushSettings()
{
    setWindowTitle(tr("Brush Settings"));
    setWindowFlags(Qt::WindowStaysOnTopHint | Qt::Tool);
    resize(400, -1);

    int lineEditWidth = 30;
    int resetButtonWidth = 30;
    QGridLayout *gridLayout = new QGridLayout;

    // Size
    QLabel *sizeLabel = new QLabel(tr("Size"));
    QSlider *sizeSlider = new QSlider(Qt::Horizontal);
    QLineEdit *sizeLineEdit = new QLineEdit;
    sizeLineEdit->setMaximumWidth(lineEditWidth);
    QPushButton *sizeButton = new QPushButton(tr("R"));
    sizeButton->setMaximumWidth(resetButtonWidth);
    QLabel *sizeMeasure = new QLabel(tr("px"));

    gridLayout->addWidget(sizeLabel, 0, 0);
    gridLayout->addWidget(sizeSlider, 0, 1);
    gridLayout->addWidget(sizeLineEdit, 0, 2);
    gridLayout->addWidget(sizeMeasure, 0, 3);
    gridLayout->addWidget(sizeButton, 0, 4);

    // Opacity
    QLabel *opacityLabel = new QLabel(tr("Opacity"));
    QSlider *opacitySlider = new QSlider(Qt::Horizontal);
    QLineEdit *opacityLineEdit = new QLineEdit;
    opacityLineEdit->setMaximumWidth(lineEditWidth);
    QPushButton *opacityButton = new QPushButton(tr("R"));
    opacityButton->setMaximumWidth(resetButtonWidth);
    QLabel *opacityMeasure = new QLabel(tr("%"));

    gridLayout->addWidget(opacityLabel, 1, 0);
    gridLayout->addWidget(opacitySlider, 1, 1);
    gridLayout->addWidget(opacityLineEdit, 1, 2);
    gridLayout->addWidget(opacityMeasure, 1, 3);
    gridLayout->addWidget(opacityButton, 1, 4);

    setLayout(gridLayout);
}

