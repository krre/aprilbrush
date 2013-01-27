import QtQuick 1.1

Rectangle {
    id: container
    height: 25
    color: "white"
    property alias pageModel: pageModel

    ListModel {
        id: pageModel
        ListElement {
            name: "Untitled 01"
        }
    }

    Component {
        id: pageDelegate
        Rectangle {
            id: pageCell
            height: listView.height
            width: 70
            color: "gray"
            Text {
                text: name
                anchors.centerIn: parent
                color: "white"
            }
        }
    }

    ListView {
        id: listView
        clip: true
        model: pageModel
        delegate: pageDelegate

        orientation: ListView.Horizontal
        spacing: 10
        width: parent.width
        height: parent.height
        anchors.margins: 5
    }
}
