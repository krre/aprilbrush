#include "CanvasItem.h"
#include "BrushEngine.h"
#include "Core.h"
#include "TabletEventFilter.h"
#include "Settings.h"
#include <QtQml>
#include <QApplication>
#include <QQmlApplicationEngine>
#include <QQuickWindow>

int main(int argc, char* argv[]) {
    QApplication app(argc, argv);
    app.setApplicationName("AprilBrush");
    app.setApplicationVersion("0.3.0");

    qmlRegisterType<AprilBrush::CanvasItem>("AprilBrush", 1, 0, "CanvasItem");

    AprilBrush::TabletEventFilter tabletEventFilter;
    app.installEventFilter(&tabletEventFilter);

    QString filePath = qApp->applicationDirPath() + "/aprilbrush.ini";
    AprilBrush::Settings settings(filePath);

    AprilBrush::BrushEngine brushEngine;
    AprilBrush::Core core;

    QQmlApplicationEngine engine;

    engine.rootContext()->setContextProperty("TabletEventFilter", &tabletEventFilter);
    engine.rootContext()->setContextProperty("Settings", &settings);
    engine.rootContext()->setContextProperty("BrushEngine", &brushEngine);
    engine.rootContext()->setContextProperty("Core", &core);
    engine.load(QUrl("qrc:/qml/Main.qml"));

    if (engine.rootObjects().isEmpty()) return EXIT_FAILURE;

    core.setMainWindow(qobject_cast<QQuickWindow*>(engine.rootObjects().at(0)));

    return app.exec();
}
