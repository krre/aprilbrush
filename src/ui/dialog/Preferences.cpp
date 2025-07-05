#include "Preferences.h"
#include "settings/Settings.h"
#include <QComboBox>
#include <QLabel>
#include <QGroupBox>
#include <QMessageBox>
#include <QFormLayout>

Preferences::Preferences(Settings* settings) : m_settings(settings) {
    setWindowTitle(tr("Preferences"));

    m_languageComboBox = new QComboBox;
    m_languageComboBox->addItem(tr("<System>"));
    m_languageComboBox->addItem(tr("English"), "en");
    m_languageComboBox->addItem(tr("Russian"), "ru");

    auto uiLayout = new QFormLayout;
    uiLayout->addRow(tr("Language:"), m_languageComboBox);
    uiLayout->itemAt(0, QFormLayout::FieldRole)->setAlignment(Qt::AlignLeft);

    auto uiGroupBox = new QGroupBox(tr("User Interface"));
    uiGroupBox->setLayout(uiLayout);

    setContentWidget(uiGroupBox);

    resizeToWidth(500);
    readSettings();
}

void Preferences::accept() {
    if (writeSettings()) {
        QMessageBox::information(this, tr("Restart requred"), tr("You must restart application"));
    }

    QDialog::accept();
}


void Preferences::readSettings() {
    int index = m_languageComboBox->findData(m_settings->applicationLanguage());

    if (index != -1) {
        m_languageComboBox->setCurrentIndex(index);
    }
}

bool Preferences::writeSettings() {
    bool restartRequired = false;
    QString language = m_languageComboBox->currentData().toString();

    if (language != m_settings->applicationLanguage()) {
        restartRequired = true;
    }

    m_settings->setApplicationLanguage(language);

    return restartRequired;
}
