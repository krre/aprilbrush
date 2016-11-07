#include "canvasitem.h"
#include "brushengine.h"
#include "core.h"
#include "tableteventfilter.h"
#include "settings.h"

#include <QtQml>
#include <QApplication>
#include <QQmlApplicationEngine>

QPointer<TabletEventFilter> tabletEventFilter;
QPointer<QQuickWindow> mainWindow;

int main(int argc, char* argv[]) {
    QApplication app(argc, argv);
    app.setApplicationName("AprilBrush");
    app.setApplicationVersion("0.3.0");

    qmlRegisterType<CanvasItem>("AprilBrush", 1, 0, "CanvasItem");

    ::tabletEventFilter = new TabletEventFilter;
    app.installEventFilter(tabletEventFilter);

    QString filePath = qApp->applicationDirPath() + "/aprilbrush.ini";
    Settings settings(filePath);
    BrushEngine brushEngine;
    Core core;

    QQmlApplicationEngine engine;

    engine.rootContext()->setContextProperty("TabletEventFilter", tabletEventFilter);
    engine.rootContext()->setContextProperty("Settings", &settings);
    engine.rootContext()->setContextProperty("BrushEngine", &brushEngine);
    engine.rootContext()->setContextProperty("Core", &core);
    engine.load(QUrl("qrc:/qml/main.qml"));

    if (engine.rootObjects().isEmpty()) return EXIT_FAILURE;

    ::mainWindow = qobject_cast<QQuickWindow *>(engine.rootObjects().at(0));

    return app.exec();
}
