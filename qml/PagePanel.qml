import QtQuick 2.0

Rectangle {
    id: container
    height: 25
    color: "#eeeeee"
    border.color: "gray"
    opacity: 0.9
    property alias pageModel: pageModel

    ListModel {
        id: pageModel
        ListElement { name: "Untitled 01" }
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
        model: pageModel
        delegate: pageDelegate

        width: parent.width
        height: parent.height
        orientation: ListView.Horizontal
        spacing: 10
        clip: true

        anchors.margins: 5
    }
}
