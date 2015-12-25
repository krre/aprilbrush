#include "canvasitem.h"
#include "brushengine.h"
#include "corelib.h"
#include "tableteventfilter.h"
#include "settings.h"

#include <QtQml>
#include <QApplication>
#include <QQmlApplicationEngine>

QPointer<TabletEventFilter> tabletEventFilter;
QPointer<QQuickWindow> mainWindow;

int main(int argc, char* argv[])
{
    QApplication app(argc, argv);
    app.setApplicationName("AprilBrush");
    app.setApplicationVersion("0.3.0");

    qmlRegisterType<CanvasItem>("AprilBrush", 1, 0, "CanvasItem");

    ::tabletEventFilter = new TabletEventFilter;
    app.installEventFilter(tabletEventFilter);

    QString filePath = qApp->applicationDirPath() + "/aprilbrush.ini";
    Settings settings(filePath);
    BrushEngine brushEngine;
    CoreLib CoreLib;

    QQmlApplicationEngine engine;
    QString storageDirPath = QDir::currentPath() + "/storage";
    QDir().mkdir(storageDirPath);
    engine.setOfflineStoragePath(storageDirPath);

    engine.rootContext()->setContextProperty("TabletEventFilter", tabletEventFilter);
    engine.rootContext()->setContextProperty("Settings", &settings);
    engine.rootContext()->setContextProperty("BrushEngine", &brushEngine);
    engine.rootContext()->setContextProperty("CoreLib", &CoreLib);
    engine.load(QUrl("qrc:/qml/main.qml"));

    ::mainWindow = qobject_cast<QQuickWindow *>(engine.rootObjects().at(0));

    return app.exec();
}
