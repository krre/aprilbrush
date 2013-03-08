import QtQuick 2.0
import "components"

Window {
    title: "Brush Library"

    Item {
        anchors.fill: parent

        ListView {
            id: listView
            model: listModel
            delegate: listDelegate
            anchors.fill: parent
            clip: true
            spacing: 5
            orientation: ListView.Horizontal
        }

        Component {
            id: listDelegate
            Rectangle {
                width: 50
                height: 50
                color: "#cfcfcf"
                Text {anchors.centerIn: parent; text: name}
                MouseArea {
                    anchors.fill: parent
                    onClicked: console.log(listView.currentItem)
                }
            }
        }

        ListModel {
            id: listModel
            ListElement {name: "Default"}
            ListElement {name: "Pencil"}
            ListElement {name: "Big"}
        }
    }
}
