import QtQuick 2.11
import QtQuick.Dialogs 1.2

FileDialog {
    Component.onCompleted: open()
    onVisibleChanged: if (!visible) destroy()
}
