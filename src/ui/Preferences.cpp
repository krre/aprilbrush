#include "Preferences.h"
#include <QtWidgets>

Preferences::Preferences(QWidget* parent) : Dialog (parent) {
    setWindowTitle(tr("Preferences"));
    auto uiGroupBox = new QGroupBox(tr("User Interface"));

    m_languageComboBox = new QComboBox;
    m_languageComboBox->addItem(tr("<System>"));
    m_languageComboBox->addItem("English", "en");
    m_languageComboBox->addItem("Russian", "ru");

    auto uiLayout = new QFormLayout(uiGroupBox);
    uiLayout->addRow(new QLabel(tr("Language:")), m_languageComboBox);
    uiLayout->itemAt(0, QFormLayout::FieldRole)->setAlignment(Qt::AlignLeft);

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
    QSettings settings;
    QString language = settings.value("language").toString();

    if (!language.isEmpty()) {
        int index = m_languageComboBox->findData(language);

        if (index != -1) {
            m_languageComboBox->setCurrentIndex(index);
        }
    }
}

bool Preferences::writeSettings() {
    bool restartRequre = false;
    QSettings settings;
    QString language = m_languageComboBox->currentData().toString();

    if (language != settings.value("language").toString()) {
        restartRequre = true;
    }

    settings.setValue("language", language);
    return restartRequre;
}
