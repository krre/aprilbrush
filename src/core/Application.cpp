#include "Application.h"
#include "settings/FileSettings.h"
#include <QTranslator>
#include <QLibraryInfo>
#include <QSettings>

Application::Application(int& argc, char* argv[]) : QApplication(argc, argv) {
    setOrganizationName(Name);
    setApplicationName(Name);
    setApplicationVersion(Version);

#ifdef Q_OS_WIN
    QSettings::setDefaultFormat(QSettings::IniFormat);
#endif

    installTranslators();
}

void Application::installTranslators() {
    FileSettings settings;
    QString language = settings.general().language;

    if (language.isEmpty()) {
        language = QLocale::system().name().split("_").first();
    }

    auto qtTranslator = new QTranslator(this);

    if (qtTranslator->load("qt_" + language, QLibraryInfo::path(QLibraryInfo::TranslationsPath))) {
        installTranslator(qtTranslator);
    }

    auto qtbaseTranslator = new QTranslator(this);

    if (qtbaseTranslator->load("qtbase_" + language, QLibraryInfo::path(QLibraryInfo::TranslationsPath))) {
        installTranslator(qtbaseTranslator);
    }

    auto appTranslator = new QTranslator(this);

    if (appTranslator->load("aprilbrush-" + language, ":/i18n")) {
        installTranslator(appTranslator);
    }
}
