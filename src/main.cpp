#include "core/Constants.h"
#include "core/EventFilter.h"
#include "ui/MainWindow.h"
#include <QApplication>
#include <QSettings>
#include <QTranslator>
#include <QLibraryInfo>

int main(int argc, char* argv[]) {
    QApplication app(argc, argv);

    QApplication::setOrganizationName(Const::App::Name);
    QApplication::setApplicationName(Const::App::Name);
    QApplication::setApplicationVersion(Const::App::Version);

    auto eventFilter = new EventFilter(&app);
    app.installEventFilter(eventFilter);

#ifdef Q_OS_WIN
    QSettings::setDefaultFormat(QSettings::IniFormat);
#endif

    QSettings settings;
    QString language = settings.value("language").toString();

    if (language.isEmpty()) {
        language = QLocale::system().name().split("_").first();
    }

    auto qtTranslator = new QTranslator(&app);

    if (qtTranslator->load("qt_" + language, QLibraryInfo::path(QLibraryInfo::TranslationsPath))) {
        QCoreApplication::installTranslator(qtTranslator);
    }

    auto appTranslator = new QTranslator(&app);

    if (appTranslator->load("app-" + language, ":/i18n")) {
        QCoreApplication::installTranslator(appTranslator);
    }

    MainWindow mainWindow;
    mainWindow.show();

    return QApplication::exec();
}
