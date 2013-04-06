import QtQuick 2.0

Item {
    id: root
    signal clicked
    property string name: "Unnamed"

    width: 55
    height: 55
    anchors.verticalCenter: parent.verticalCenter

    Rectangle {
        radius: 5
        anchors.fill: parent
        antialiasing: true
        color: mouseArea.pressed ? "#cccccc" : "#e6e6e6"
        border.color: "gray"
    }

    Text {
        text: name
        anchors.fill: parent
        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter
        wrapMode: Text.WordWrap
        clip: true
    }

    MouseArea {
        id: mouseArea
        anchors.fill: parent
        onReleased: root.clicked()
    }
}
