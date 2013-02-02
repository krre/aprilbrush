import QtQuick 2.0

Item {
    id: container
    width: 200
    height: 25
    signal pressFileItem(string itemName)

    ListModel {
        id: fileModel
        ListElement {name: "New"}
        ListElement {name: "Open"}
        ListElement {name: "Save"}
    }

    Component {
        id: fileDelegate
        Rectangle {
            id: fileRectangle
            width: 40
            height: container.height
            color: fileMouseArea.containsMouse ? "black" : "gray"
            Text {
                id: fileText
                text: name
                color: "white"
                anchors.centerIn: parent
            }

            MouseArea {
                id: fileMouseArea
                anchors.fill: parent
                hoverEnabled: true
                onClicked: container.pressFileItem(fileText.text)
            }
        }
    }

    ListView {
        model: fileModel
        delegate: fileDelegate
        orientation: ListView.Horizontal
        width: parent.width
    }

}
