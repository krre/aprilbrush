#include "cpp/canvasitem.h"
#include "cpp/corelib.h"
#include "cpp/tableteventfilter.h"

#include <QtQml>
#include <QApplication>
#include <QQmlApplicationEngine>

QPointer<TabletEventFilter> tabletEventFilter;

int main(int argc, char* argv[])
{
    QApplication app(argc, argv);

    qmlRegisterType<CanvasItem>("AprilBrush", 1, 0, "CanvasItem");
    qmlRegisterType<CoreLib>("AprilBrush", 1, 0, "CoreLib");

    ::tabletEventFilter = new TabletEventFilter;
//    app.installEventFilter(&tabletEventFilter);

    QQmlApplicationEngine engine;
    QString storageDirPath = QDir::currentPath() + "/storage";
    QDir().mkdir(storageDirPath);
    engine.setOfflineStoragePath(storageDirPath);
    engine.rootContext()->setContextProperty("TabletEventFilter", tabletEventFilter);
    engine.load(QUrl("qrc:///qml/Main.qml"));

    return app.exec();
}
