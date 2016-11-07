import QtQuick 2.8
import QtQuick.Dialogs 1.2

MessageDialog {
    title: Qt.application.name
    onVisibleChanged: if (!visible) destroy()
    Component.onCompleted: open()
}
