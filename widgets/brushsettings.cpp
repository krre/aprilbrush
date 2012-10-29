#include "brushsettings.h"

BrushSettings::BrushSettings()
{
    setWindowTitle(tr("Brush Settings"));
    setModal(true);

    QLabel *sizeLabel = new QLabel("Size");
    QSlider *sizeSlider = new QSlider(Qt::Horizontal);
    QTextEdit *sizeTextEdit = new QTextEdit;
    QHBoxLayout *horizontalLayoutSize = new QHBoxLayout;
    horizontalLayoutSize->addWidget(sizeLabel);
    horizontalLayoutSize->addWidget(sizeSlider);
    horizontalLayoutSize->addWidget(sizeTextEdit);

    buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Apply | QDialogButtonBox::Cancel);

    QVBoxLayout *verticalLayout = new QVBoxLayout;
    verticalLayout->addLayout(horizontalLayoutSize);
    verticalLayout->addWidget(buttonBox);
    setLayout(verticalLayout);
}

