import QtQuick 2.0

Rectangle {
    property string title: "Unnamed"
    //property alias closeArea: closeHandler
    default property alias content: stack.children
    id: window
    width: 200
    height: 200
    color: "#eeeeee"
    border.color: "gray"
    opacity: 0.9
    radius: 7
    antialiasing: true
    MouseArea {
        anchors.fill: parent
        drag.target: parent
    }

    Column {
        // Header
        Item {
            id: head;
            //color: "#c8c8c8"
            width: window.width;
            height: 25
            Text {
                anchors.left: parent.left
                anchors.verticalCenter: parent.verticalCenter
                anchors.margins: 10
                text: title
                font.pointSize: 8
            }
        }
        // Content stack
        Item {
            id: stack
            //color: "green";
            width: window.width;
            height: window.height - head.height
        }
    }

    // Close handler
    Rectangle {
        id: closeHandler
        width: 20
        height: 20
        anchors.top: parent.top
        anchors.right: parent.right
        color: closeMouseArea.containsMouse ? "red" : "transparent"
        Text {
            text: "X"
            anchors.centerIn: parent
            font.bold: true
            color: closeMouseArea.containsMouse ? "white" : "transparent"
        }

        MouseArea {
            id: closeMouseArea
            anchors.fill: parent
            hoverEnabled: true
            onClicked: window.visible = false
        }
    }

    // Resize handler
    Rectangle {
        id: resizeHandler
        width: 20
        height: 20
        anchors.bottom: parent.bottom
        anchors.right: parent.right
        clip: true
        color: resizeMouseArea.containsMouse ? "gray" : "transparent"
        Text {
            text: "="
            anchors.centerIn: parent
            font.bold: true
            color: resizeMouseArea.containsMouse ? "white" : "transparent"
        }

        MouseArea {
            id: resizeMouseArea
            property point grabPoint: Qt.point(0, 0)
            property bool grabFlag: false
            anchors.fill: parent
            hoverEnabled: true
            onPressed: {
                grabPoint = Qt.point(mouseX, mouseY)
                grabFlag = true
            }
            onReleased: grabFlag = false
            onPositionChanged: {
                if (grabFlag) {
                    window.width = window.width + (mouseX - grabPoint.x)
                    window.height = window.height + (mouseY - grabPoint.y)
                }
            }
        }
    }
}
