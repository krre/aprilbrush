#include "canvasitem.h"
#include "brushengine.h"
#include "corelib.h"
#include "tableteventfilter.h"
#include "settings.h"

#include <QtQml>
#include <QApplication>
#include <QQmlApplicationEngine>

QPointer<TabletEventFilter> tabletEventFilter;

int main(int argc, char* argv[])
{
    QApplication app(argc, argv);
    app.setApplicationName("AprilBrush");
    app.setApplicationVersion("0.3.0");

    qmlRegisterType<CanvasItem>("AprilBrush", 1, 0, "CanvasItem");
    qmlRegisterType<CoreLib>("AprilBrush", 1, 0, "CoreLib");

    ::tabletEventFilter = new TabletEventFilter;
    app.installEventFilter(tabletEventFilter);

    QString filePath = qApp->applicationDirPath() + "/aprilbrush.ini";
    Settings settings(filePath);
    BrushEngine brushEngine;

    QQmlApplicationEngine engine;
    QString storageDirPath = QDir::currentPath() + "/storage";
    QDir().mkdir(storageDirPath);
    engine.setOfflineStoragePath(storageDirPath);
    engine.rootContext()->setContextProperty("TabletEventFilter", tabletEventFilter);
    engine.rootContext()->setContextProperty("Settings", &settings);
    engine.rootContext()->setContextProperty("BrushEngine", &brushEngine);
    engine.load(QUrl("qrc:/qml/main.qml"));

    return app.exec();
}
