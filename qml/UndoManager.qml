import QtQuick 2.0
import "components"

Window {
    id: root
    title: "Undo History"
    //property alias currentUndo: value
    Item {
        anchors.fill: parent

        ListView {
            id: undoView
            model: undoModel
            delegate: undoDelegate

            width: parent.width
            height: 150

            orientation: ListView.Vertical
            clip: true
            spacing: 4
        }

        Component {
            id: undoDelegate
            Rectangle {
                width: parent.width
                height: 20
                color: "transparent"
                border.width: 1
                border.color: "gray"
                radius: 5
                antialiasing: true
                Text {
                    text: name
                    anchors.verticalCenter: parent.verticalCenter
                    anchors.left: parent.left
                    anchors.leftMargin: 10
                }
            }
        }
    }
}
