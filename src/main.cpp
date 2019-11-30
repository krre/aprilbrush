#include "core/Constants.h"
#include "cpp/CanvasItem.h"
#include "cpp/BrushEngine.h"
#include "cpp/Core.h"
#include "cpp/TabletEventFilter.h"
#include "cpp/Settings.h"
#include <QtQml>
#include <QApplication>
#include <QQmlApplicationEngine>
#include <QQuickWindow>

int main(int argc, char* argv[]) {
    QApplication app(argc, argv);

    QApplication::setOrganizationName(Const::App::Name);
    QApplication::setApplicationName(Const::App::Name);
    QApplication::setApplicationVersion(Const::App::Version);

    qmlRegisterType<CanvasItem>("AprilBrush", 1, 0, "CanvasItem");

    TabletEventFilter tabletEventFilter;
    app.installEventFilter(&tabletEventFilter);

    QString filePath = QApplication::applicationDirPath() + "/aprilbrush.ini";
    Settings settings(filePath);

    BrushEngine brushEngine;
    Core core;

    QQmlApplicationEngine engine;

    engine.rootContext()->setContextProperty("TabletEventFilter", &tabletEventFilter);
    engine.rootContext()->setContextProperty("Settings", &settings);
    engine.rootContext()->setContextProperty("BrushEngine", &brushEngine);
    engine.rootContext()->setContextProperty("Core", &core);
    engine.load(QUrl("qrc:/qml/Main.qml"));

    if (engine.rootObjects().isEmpty()) return EXIT_FAILURE;

    core.setMainWindow(qobject_cast<QQuickWindow*>(engine.rootObjects().at(0)));

    return QApplication::exec();
}
