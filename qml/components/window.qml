import QtQuick 2.0

Rectangle {
    id: root
    property string title: "Unnamed"
    default property alias content: stack.children
    property int defaultWidth: 200
    property int defaultHeight: 200
    property int indent: 10

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
        onPressed: {
            // Moving a item on top of the scene
            var maxZ = 0
            for (var i = 0; i < root.parent.children.length; i++)
                if (root.parent.children[i].z > maxZ) maxZ = root.parent.children[i].z
            root.z = ++maxZ
        }
    }

    Column {
        // Header
        Item {
            id: head;
            width: root.width;
            height: 25
            Text {
                anchors.left: parent.left
                anchors.verticalCenter: parent.verticalCenter
                anchors.margins: indent
                text: title
                font.pointSize: 8
            }
        }
        // Content stack
        Item {
            id: stack
            width: root.width - indent * 2;
            height: root.height - head.height
            anchors.horizontalCenter: parent.horizontalCenter
        }
    }

    CloseButton {
        anchors.top: parent.top
        anchors.right: parent.right
        onClicked: root.visible = false
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
                    var newWidth = root.width + (mouseX - grabPoint.x)
                    root.width = newWidth < defaultWidth ? defaultWidth : newWidth
                    var newHeight = root.height + (mouseY - grabPoint.y)
                    root.height = newHeight < defaultHeight ? defaultHeight : newHeight
                }
            }
        }
    }
}
