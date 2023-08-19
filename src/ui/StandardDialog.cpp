#include "StandardDialog.h"
#include <QtWidgets>

StandardDialog::StandardDialog(QWidget* parent) : QDialog(parent) {
    m_buttonBox = new QDialogButtonBox;
    m_buttonBox->setOrientation(Qt::Horizontal);
    m_buttonBox->setStandardButtons(QDialogButtonBox::Ok|QDialogButtonBox::Cancel);

    connect(m_buttonBox, &QDialogButtonBox::accepted, this, &QDialog::accept);
    connect(m_buttonBox, &QDialogButtonBox::rejected, this, &QDialog::reject);

    auto verticalLayout = new QVBoxLayout;
    verticalLayout->addWidget(m_buttonBox);
    setLayout(verticalLayout);
}

QDialogButtonBox* StandardDialog::buttonBox() const {
    return m_buttonBox;
}

void StandardDialog::setContentWidget(QWidget* contentWidget, bool stretchAfter) {
    auto verticalLayout = static_cast<QVBoxLayout*>(layout());
    verticalLayout->insertWidget(0, contentWidget);

    if (stretchAfter) {
        verticalLayout->insertStretch(1);
    }
}

void StandardDialog::setContentLayout(QLayout* contentLayout, bool stretchAfter) {
    auto verticalLayout = static_cast<QVBoxLayout*>(layout());
    verticalLayout->insertLayout(0, contentLayout);

    if (stretchAfter) {
        verticalLayout->insertStretch(1);
    }
}

void StandardDialog::resizeToWidth(int width) {
    resize(width, sizeHint().height());
}
