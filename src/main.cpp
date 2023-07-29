#include "core/Constants.h"
#include "core/Settings.h"
#include "ui/MainWindow.h"
#include <QApplication>
#include <QTranslator>
#include <QLibraryInfo>

int main(int argc, char* argv[]) {
    QApplication app(argc, argv);
    app.setOrganizationName(Const::App::Name);
    app.setApplicationName(Const::App::Name);
    app.setApplicationVersion(Const::App::Version);

#ifdef Q_OS_WIN
    QSettings::setDefaultFormat(QSettings::IniFormat);
#endif

    QString language = Settings::value<General::Language>();

    if (language.isEmpty()) {
        language = QLocale::system().name().split("_").first();
    }

    auto qtTranslator = new QTranslator(&app);

    if (qtTranslator->load("qt_" + language, QLibraryInfo::path(QLibraryInfo::TranslationsPath))) {
        app.installTranslator(qtTranslator);
    }

    auto appTranslator = new QTranslator(&app);

    if (appTranslator->load("aprilbrush-" + language, ":/i18n")) {
        app.installTranslator(appTranslator);
    }

    MainWindow mainWindow;
    mainWindow.show();

    return app.exec();
}
