#include "NewImage.h"
#include "Canvas.h"
#include "settings/Settings.h"
#include <QtWidgets>

NewImage::NewImage(const QString& name, Settings* settings, QWidget* parent) : StandardDialog(parent), m_settings(settings) {
    setWindowTitle(tr("Create New Image"));

    m_nameEdit = new QLineEdit(name);
    connect(m_nameEdit, &QLineEdit::textChanged, this, &NewImage::onNameChanged);

    m_widthSpinBox = new QSpinBox;
    m_heightSpinBox = new QSpinBox;

    setupSpinBox(m_widthSpinBox);
    setupSpinBox(m_heightSpinBox);

    auto sizeButton = new QPushButton(tr("Screen Size"));
    connect(sizeButton, &QPushButton::clicked, this, &NewImage::resetSize);

    auto formLayout = new QFormLayout;
    formLayout->addRow(tr("Name:"), m_nameEdit);
    formLayout->addRow(tr("Width:"), m_widthSpinBox);
    formLayout->addRow(tr("Height:"), m_heightSpinBox);
    formLayout->addRow(sizeButton);

    formLayout->itemAt(formLayout->indexOf(m_widthSpinBox))->setAlignment(Qt::AlignLeft);
    formLayout->itemAt(formLayout->indexOf(m_heightSpinBox))->setAlignment(Qt::AlignLeft);
    formLayout->itemAt(formLayout->indexOf(sizeButton))->setAlignment(Qt::AlignLeft);

    setContentLayout(formLayout);
    resizeToWidth(400);
    readSettings();
    m_nameEdit->setFocus();
}

QString NewImage::name() const {
    return m_nameEdit->text();
}

QSize NewImage::size() const {
    return QSize(m_widthSpinBox->value(), m_heightSpinBox->value());
}

void NewImage::accept() {
    writeSettings();
    QDialog::accept();
}

void NewImage::resetSize() {
    QSize canvasSize = Canvas::defaultSize();
    m_widthSpinBox->setValue(canvasSize.width());
    m_heightSpinBox->setValue(canvasSize.height());
}

void NewImage::onNameChanged(const QString& text) {
    buttonBox()->button(QDialogButtonBox::Ok)->setEnabled(!text.isEmpty());
}

void NewImage::readSettings() {
    QSize size = m_settings->newImage().size;

    if (size.isValid()) {
        m_widthSpinBox->setValue(size.width());
        m_heightSpinBox->setValue(size.height());
    } else {
        resetSize();
    }
}

void NewImage::writeSettings() {
    Settings::NewImage newImage = m_settings->newImage();
    newImage.size = QSize(m_widthSpinBox->value(), m_heightSpinBox->value());

    m_settings->setNewImage(newImage);
}

void NewImage::setupSpinBox(QSpinBox* spinBox) {
    spinBox->setMinimumWidth(80);
    spinBox->setRange(1, 10000);
}
