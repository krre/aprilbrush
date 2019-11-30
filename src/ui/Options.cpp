#include "Options.h"
#include <QtWidgets>

Options::Options(QWidget* parent) : QDialog (parent) {
    setWindowTitle(tr("Options"));
    auto layout = new QVBoxLayout;
    auto groupBoxUi = new QGroupBox(tr("User Interface"));
    auto gridLayoutUi = new QGridLayout;
    gridLayoutUi->setColumnStretch(1, 1);

    // Language
    gridLayoutUi->addWidget(new QLabel(tr("Language:")), 0, 0);

    m_languageComboBox = new QComboBox;
    m_languageComboBox->addItem(tr("<System>"));
    m_languageComboBox->addItem("English", "en");
    m_languageComboBox->addItem("Russian", "ru");

    gridLayoutUi->addWidget(m_languageComboBox, 0, 1, Qt::AlignLeft);
    groupBoxUi->setLayout(gridLayoutUi);

    layout->addWidget(groupBoxUi);
    layout->addStretch(1);

    auto buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel);
    layout->addWidget(buttonBox);

    connect(buttonBox, &QDialogButtonBox::accepted, this, &QDialog::accept);
    connect(buttonBox, &QDialogButtonBox::rejected, this, &QDialog::reject);

    setLayout(layout);
    resize(500, 100);
    readSettings();
}

void Options::accept() {
    if (writeSettings()) {
        QMessageBox::information(this, tr("Restart requred"), tr("You must restart application"));
    }

    QDialog::accept();
}


void Options::readSettings() {
    QSettings settings;
    QString language = settings.value("language").toString();

    if (!language.isEmpty()) {
        int index = m_languageComboBox->findData(language);

        if (index != -1) {
            m_languageComboBox->setCurrentIndex(index);
        }
    }
}

bool Options::writeSettings() {
    bool restartRequre = false;
    QSettings settings;
    QString language = m_languageComboBox->currentData().toString();

    if (language != settings.value("language").toString()) {
        restartRequre = true;
    }

    settings.setValue("language", language);
    return restartRequre;
}
