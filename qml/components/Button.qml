import QtQuick 2.0

Rectangle {
    id: root
    property alias title: label.text
    signal clicked()

    width: 50
    height: 20
    color: "lightgray"
    radius: 5
    antialiasing: true
    Text {
        id: label
        text: qsTr("Button")
        anchors.centerIn: parent
    }
    MouseArea {
        anchors.fill: parent
        onClicked: root.clicked()
    }
}
