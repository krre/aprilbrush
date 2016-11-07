import QtQuick 2.8
import QtQuick.Dialogs 1.2

FileDialog {
    Component.onCompleted: open()
    onVisibleChanged: if (!visible) destroy()
}
