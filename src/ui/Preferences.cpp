#include "Preferences.h"
#include "settings/Settings.h"
#include <QtWidgets>

Preferences::Preferences(Settings* settings, QWidget* parent)
    : StandardDialog (parent), m_settings(settings) {
    setWindowTitle(tr("Preferences"));

    m_languageComboBox = new QComboBox;
    m_languageComboBox->addItem(tr("<System>"));
    m_languageComboBox->addItem(tr("English"), "en");
    m_languageComboBox->addItem(tr("Russian"), "ru");

    auto uiLayout = new QFormLayout;
    uiLayout->addRow(new QLabel(tr("Language:")), m_languageComboBox);
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
    int index = m_languageComboBox->findData(m_settings->application().language);

    if (index != -1) {
        m_languageComboBox->setCurrentIndex(index);
    }
}

bool Preferences::writeSettings() {
    bool restartRequired = false;
    QString language = m_languageComboBox->currentData().toString();
    Settings::Application general = m_settings->application();

    if (language != general.language) {
        restartRequired = true;
    }

    general.language = language;
    m_settings->setApplication(general);

    return restartRequired;
}
