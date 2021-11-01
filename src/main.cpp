#include "core/Constants.h"
#include "ui/MainWindow.h"
#include "cpp/CanvasItem.h"
#include "cpp/BrushEngine.h"
#include "cpp/Core.h"
#include "cpp/TabletEventFilter.h"
#include "cpp/Settings.h"
#include <QtQml>
#include <QApplication>
#include <QQmlApplicationEngine>
#include <QQuickWindow>
#include <QSettings>

int main(int argc, char* argv[]) {
    QApplication app(argc, argv);

    QApplication::setOrganizationName(Const::App::Name);
    QApplication::setApplicationName(Const::App::Name);
    QApplication::setApplicationVersion(Const::App::Version);

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
