import QtQuick 2.0

Rectangle {
    id: root
    property alias text: label.text
    property bool closable: true
    signal clicked()
    signal closed()

    width: parent.width
    height: 20
    color: "lightgray"
    border.width: 1
    border.color: "gray"
    radius: 5
    antialiasing: true
    Text {
        id: label
        text: qsTr("Item")
        anchors.verticalCenter: parent.verticalCenter
        anchors.left: parent.left
        anchors.leftMargin: 10
    }
    MouseArea {
        anchors.fill: parent
        onClicked: root.clicked()
    }
    CloseButton {
        visible: closable
        anchors.verticalCenter: parent.verticalCenter
        anchors.right: parent.right
        anchors.rightMargin: 2
        onClicked: closed()
    }
}
