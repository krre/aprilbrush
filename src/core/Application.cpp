#include "Application.h"
#include "core/Constants.h"
#include "core/Settings.h"
#include <QTranslator>
#include <QLibraryInfo>

Application::Application(int argc, char* argv[]) : QApplication(argc, argv) {
    setOrganizationName(Const::App::Name);
    setApplicationName(Const::App::Name);
    setApplicationVersion(Const::App::Version);

#ifdef Q_OS_WIN
    QSettings::setDefaultFormat(QSettings::IniFormat);
#endif

    QString language = Settings::value<General::Language>();

    if (language.isEmpty()) {
        language = QLocale::system().name().split("_").first();
    }

    auto qtTranslator = new QTranslator(this);

    if (qtTranslator->load("qt_" + language, QLibraryInfo::path(QLibraryInfo::TranslationsPath))) {
        installTranslator(qtTranslator);
    }

    auto appTranslator = new QTranslator(this);

    if (appTranslator->load("aprilbrush-" + language, ":/i18n")) {
        installTranslator(appTranslator);
    }
}
