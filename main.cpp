#include <QGuiApplication>
#include <QQuickView>
#include <QUrl>

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);
    QQuickView view;
    view.setSource(QUrl("qrc:qml/main.qml"));
    view.show();

    return app.exec();
}
