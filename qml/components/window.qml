import QtQuick 2.0

Rectangle {
    property string title: "Unnamed"
    default property alias content: stack.children
    property int defaultWidth: 200
    property int defaultHeight: 200

    id: window
    width: defaultWidth
    height: defaultHeight
    color: "#eeeeee"
    border.color: "gray"
    //opacity: 0.9
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
            width: window.width;
            height: window.height - head.height
        }
    }

    // Close handler
    Item {
        id: closeHandler
        width: 20
        height: 20
        anchors.top: parent.top
        anchors.right: parent.right
        Text {
            text: "x"
            anchors.centerIn: parent
            font.pointSize: 10
            font.bold: closeMouseArea.containsMouse ? true : false
        }

        MouseArea {
            id: closeMouseArea
            anchors.fill: parent
            hoverEnabled: true
            onClicked: window.visible = false
        }
    }

    // Resize handler
    Item {
        id: resizeHandler
        width: 20
        height: 20
        anchors.bottom: parent.bottom
        anchors.right: parent.right
        Text {
            text: "="
            anchors.centerIn: parent
            font.pointSize: 11
            font.bold: resizeMouseArea.containsMouse ? true : false
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
                    var newWidth = window.width + (mouseX - grabPoint.x)
                    window.width = newWidth < defaultWidth ? defaultWidth : newWidth
                    var newHeight = window.height + (mouseY - grabPoint.y)
                    window.height = newHeight < defaultHeight ? defaultHeight : newHeight
                }
            }
        }
    }
}
