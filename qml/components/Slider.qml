import QtQuick 2.0

Item {
    id:  slider
    height: 25
    width: parent.width
    property string name: "Slider"
    property int min: 0
    property int max: 1
    property int init: min + (max - min) / 2
    property int value: min + (max - min) * (handle.x / (scale.width - handle.width))

    Component.onCompleted: handle.x = (init - min) / (max - min) * (scale.width - handle.width)

    Item {
        height: 10
        width: parent.width

        Text {
            text: name
            anchors.left: parent.left
            anchors.margins: 10
        }
        Text {
            text: value
            anchors.right: parent.right
            anchors.margins: 10
        }
    }

    Item {
        id: scale
        height: 12
        width: parent.width - 20
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.bottom: parent.bottom
        Rectangle {
            width: parent.width
            height: parent.height
            radius: 5
            antialiasing: true
            border.color: "gray"
            opacity: 0.7
        }

        Rectangle {
            id: handle
            width: 20
            height: parent.height
            radius: 5
            antialiasing: true
            color: "gray"
            MouseArea {
                anchors.fill: parent
                drag.target: parent
                drag.axis: Drag.XAxis
                drag.minimumX: 0
                drag.maximumX: scale.width - parent.width
            }
        }
    }
}
