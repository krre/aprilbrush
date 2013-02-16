import QtQuick 2.0

Rectangle {
    width: 200
    height: 200
    color: "#eeeeee"
    border.color: "gray"
    opacity: 0.9

    MouseArea {
        anchors.fill: parent
        drag.target: parent
    }

}
