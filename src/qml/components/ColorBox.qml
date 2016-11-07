import QtQuick 2.8
import QtQuick.Dialogs 1.2

Rectangle {
    id: root
    width: 20
    height: 20
    color: "white"
    border.color: "black"

    signal accepted(var color)

    MouseArea {
        anchors.fill: parent
        onClicked: {
            colorDialog.color = root.color
            colorDialog.open()
        }
    }

    ColorDialog {
        id: colorDialog
        title: qsTr("Color:")
        onAccepted: {
            root.color = color
            root.accepted(color)
        }
    }
}
