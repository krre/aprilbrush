#include <QApplication>
#include <QDeclarativeView>
#include <QUrl>
#include <QIcon>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    QDeclarativeView view;
    //view.setSource(QUrl("qrc:qml/qml/main.qml"));
    view.setSource(QUrl("../../Projects/aprilbrush/qml/main.qml"));
    view.setResizeMode(QDeclarativeView::SizeRootObjectToView);
    view.setWindowIcon(QIcon(":/icons/Butterfly_128x128.png"));
    view.resize(1100, 700);
    view.show();

    return app.exec();
}
