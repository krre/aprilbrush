#include "NewImage.h"
#include <QtWidgets>

NewImage::NewImage(QWidget *parent) : QDialog(parent) {
    setWindowTitle(tr("New Image"));

    auto layout = new QVBoxLayout;
    setLayout(layout);

    auto gridLayout = new QGridLayout;
    gridLayout->setColumnStretch(1, 1);
    layout->addLayout(gridLayout);

    gridLayout->addWidget(new QLabel(tr("Name:")), 0, 0);
    m_nameLineEdit = new QLineEdit;
    gridLayout->addWidget(m_nameLineEdit, 0, 1);

    gridLayout->addWidget(new QLabel(tr("Width:")), 1, 0);
    m_widthSpinBox = new QSpinBox;
    m_widthSpinBox->setMinimumWidth(80);
    gridLayout->addWidget(m_widthSpinBox, 1, 1, Qt::AlignLeft);

    gridLayout->addWidget(new QLabel(tr("Height:")), 2, 0);
    m_heightSpinBox = new QSpinBox;
    m_heightSpinBox->setMinimumWidth(80);
    gridLayout->addWidget(m_heightSpinBox, 2, 1, Qt::AlignLeft);

    auto sizeButton = new QPushButton(tr("Screen Size"));
    gridLayout->addWidget(sizeButton, 3, 0, 1, -1, Qt::AlignLeft);
    connect(sizeButton, &QPushButton::clicked, this, &NewImage::resetToScreenSize);

    layout->addStretch(1);

    auto buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel);
    layout->addWidget(buttonBox);

    resize(400, 0);
    resetToScreenSize();

    connect(buttonBox, &QDialogButtonBox::accepted, this, &QDialog::accept);
    connect(buttonBox, &QDialogButtonBox::rejected, this, &QDialog::reject);
}

void NewImage::resetToScreenSize() {
    qDebug() << "reset";
}
