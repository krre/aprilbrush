import QtQuick 2.4
import QtQuick.Controls 1.3
import QtQuick.Layouts 1.1

Rectangle {
    id: root
    property alias title: title.text
    default property alias content: contentArea.children
    property var storage: []
    property color mouseAreaColor: Qt.darker(root.color, 1.2)
    implicitWidth: 200
    implicitHeight: 200
    color: mainRoot.sysPalette.window
    border.color: "#5d5d5d"
    visible: false

    Component.onCompleted: {
        var defaultStorage = ["x", "y", "z", "width", "height", "visible"]
        for (var i = 0; i < defaultStorage.length; i++) {
            storage.push(defaultStorage[i])
        }
    }

    // dragging and selecting
    MouseArea {
        anchors.fill: parent
        hoverEnabled: true // need for correct changing cursor shape
        drag.target: root
        drag.threshold: 1
        onPressed: {
            // moving item on top of scene
            var maxZ = 0
            for (var i = 0; i < mainRoot.contentItem.children.length; i++) {
                maxZ = Math.max(mainRoot.contentItem.children[i].z, maxZ)
            }
            root.z = ++maxZ
        }
    }

    ColumnLayout {
        anchors.fill: parent
        spacing: 0

        // header
        Rectangle {
            Layout.fillWidth: true
            Layout.preferredHeight: 25
            color: mouseAreaColor
            border.color: root.border.color

            Label {
                id: title
                anchors.centerIn: parent
                text: "Title"
                font.pixelSize: 13
            }

            ToolButton {
                anchors.top: parent.top
                anchors.right: parent.right
                text: "x"
                width: 20
                height: 20
                onClicked: root.visible = false
            }
        }

        // content container
        Item {
            Layout.fillHeight: true
            Layout.fillWidth: true

            Item {
                id: contentArea
                anchors.fill: parent
                anchors.margins: 5
            }
        }
    }

    // resize handler
    Rectangle {
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        width: 15
        height: 15
        color: sizeMouseArea.containsMouse ? mouseAreaColor : "transparent"
        border.color: sizeMouseArea.containsMouse ? root.border.color : "transparent"

        MouseArea {
            id: sizeMouseArea
            property point pressedPos
            anchors.fill: parent
            hoverEnabled: true

            onPressed: pressedPos = Qt.point(mouseX, mouseY)
            onPositionChanged: {
                if (pressed) {
                    root.width = Math.max(root.implicitWidth, root.width + mouse.x - pressedPos.x)
                    root.height = Math.max(root.implicitHeight, root.height + mouse.y - pressedPos.y)
                }
            }
        }
    }
}

