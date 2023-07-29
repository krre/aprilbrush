#include "NewImage.h"
#include "Canvas.h"
#include <QtWidgets>

NewImage::NewImage(const QString& name, QWidget* parent) : Dialog(parent) {
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

    auto columnLayout = new QVBoxLayout;
    columnLayout->addLayout(formLayout);
    columnLayout->addWidget(sizeButton, 0, Qt::AlignLeft);
    columnLayout->addStretch();

    setContentLayout(columnLayout);
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
