import QtQuick 2.0

Item {
    id: root
    signal clicked()

    width: 20
    height: 20

    Text {
        text: "x"
        anchors.centerIn: parent
        font.pointSize: 10
        font.bold: mouseArea.containsMouse ? true : false
    }

    MouseArea {
        id: mouseArea
        anchors.fill: parent
        hoverEnabled: true
        onClicked: root.clicked()
    }
}
