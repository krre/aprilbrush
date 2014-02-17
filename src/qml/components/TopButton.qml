import QtQuick 2.2

Rectangle {
    id: root
    property alias title: title.text
    width: 120
    height: title.height * 1.2
    radius: height / 2
    color: mouseArea.pressed? "#222222" : mouseArea.containsMouse ? "#474747" : "black"
    opacity: 0.8

    Text {
        id: title
        color: "white"
        anchors.centerIn: parent
    }

    signal clicked

    MouseArea {
        id: mouseArea
        anchors.fill: parent
        hoverEnabled: true
        onClicked: root.clicked()
    }
}
