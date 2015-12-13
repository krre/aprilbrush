import QtQuick 2.5
import QtQuick.Dialogs 1.1

FileDialog {
    Component.onCompleted: open()
    onVisibleChanged: if (!visible) destroy()
}
