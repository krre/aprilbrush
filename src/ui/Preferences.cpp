#include "Preferences.h"
#include "core/Settings.h"
#include <QtWidgets>

Preferences::Preferences(QWidget* parent) : StandardDialog (parent) {
    setWindowTitle(tr("Preferences"));

    m_languageComboBox = new QComboBox;
    m_languageComboBox->addItem(tr("<System>"));
    m_languageComboBox->addItem("English", "en");
    m_languageComboBox->addItem("Russian", "ru");

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
    QString language = Settings::value<General::Language>();

    int index = m_languageComboBox->findData(language);

    if (index != -1) {
        m_languageComboBox->setCurrentIndex(index);
    }
}

bool Preferences::writeSettings() {
    bool restartRequre = false;
    QString language = m_languageComboBox->currentData().toString();

    if (language != Settings::value<General::Language>()) {
        restartRequre = true;
    }

    Settings::setValue<General::Language>(language);
    return restartRequre;
}
