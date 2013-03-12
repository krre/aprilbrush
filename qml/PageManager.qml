import QtQuick 2.0

Rectangle {
    width: 600
    height: 40
    color: "#eeeeee"
    border.color: "gray"
    radius: 7
    antialiasing: true

    ListView {
        id: pagesView
        model: pagesModel
        delegate: pagesDelegate

        width: parent.width - 8
        height: parent.height - 8
        orientation: ListView.Horizontal
        anchors.centerIn: parent
        spacing: 5
        clip: true

    }

    ListModel {
        id: pagesModel
        ListElement { name: "Page-01" }
        ListElement { name: "Page-02" }
    }

    Component {
        id: pagesDelegate
        Rectangle {
            width: 100
            height: pagesView.height
            color: "lightgray"
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
