#include "NewImage.h"
#include "core/Utils.h"
#include <QtWidgets>

NewImage::NewImage(QWidget* parent) : QDialog(parent) {
    setWindowTitle(tr("Create New Image"));

    auto layout = new QVBoxLayout;
    setLayout(layout);

    auto gridLayout = new QGridLayout;
    gridLayout->setColumnStretch(1, 1);
    layout->addLayout(gridLayout);

    gridLayout->addWidget(new QLabel(tr("Width:")), 1, 0);
    m_widthSpinBox = new QSpinBox;
    setupSpinBox(m_widthSpinBox);
    gridLayout->addWidget(m_widthSpinBox, 1, 1, Qt::AlignLeft);

    gridLayout->addWidget(new QLabel(tr("Height:")), 2, 0);
    m_heightSpinBox = new QSpinBox;
    setupSpinBox(m_heightSpinBox);
    gridLayout->addWidget(m_heightSpinBox, 2, 1, Qt::AlignLeft);

    auto sizeButton = new QPushButton(tr("Screen Size"));
    gridLayout->addWidget(sizeButton, 3, 0, 1, -1, Qt::AlignLeft);
    connect(sizeButton, &QPushButton::clicked, this, &NewImage::resetSize);

    layout->addStretch(1);

    auto buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel);
    layout->addWidget(buttonBox);

    resize(400, 0);
    readSettings();

    connect(buttonBox, &QDialogButtonBox::accepted, this, &QDialog::accept);
    connect(buttonBox, &QDialogButtonBox::rejected, this, &QDialog::reject);
}

QSize NewImage::imageSize() const {
    return QSize(m_widthSpinBox->value(), m_heightSpinBox->value());
}

void NewImage::accept() {
    writeSettings();
    QDialog::accept();
}

void NewImage::resetSize() {
    QSize canvasSize = Utils::defaultCanvasSize();
    m_widthSpinBox->setValue(canvasSize.width());
    m_heightSpinBox->setValue(canvasSize.height());
}

void NewImage::readSettings() {
    QSettings settings;
    settings.beginGroup("NewImage");

    if (settings.contains("width")) {
        m_widthSpinBox->setValue(settings.value("width").toInt());
        m_heightSpinBox->setValue(settings.value("height").toInt());
    } else {
        resetSize();
    }
}

void NewImage::writeSettings() {
    QSettings settings;
    settings.beginGroup("NewImage");
    settings.setValue("width", m_widthSpinBox->value());
    settings.setValue("height", m_heightSpinBox->value());
}

void NewImage::setupSpinBox(QSpinBox* spinBox) {
    spinBox->setMinimumWidth(80);
    spinBox->setRange(1, 10000);
}
