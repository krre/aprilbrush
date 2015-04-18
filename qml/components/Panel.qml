import QtQuick 2.4
import QtQuick.Controls 1.3
import QtQuick.Layouts 1.1
import QtQuick.Controls.Private 1.0

Rectangle {
    id: root
    property alias title: title.text
    default property alias content: contentArea.children
    property var storage
    property color mouseAreaColor: Qt.darker(root.color, 1.2)
    implicitWidth: 200
    implicitHeight: 200
    color: mainRoot.sysPalette.window
    border.color: "#5d5d5d"
    Drag.active: dragMouseArea.drag.active

    function defaultStorage() {
        return ["x", "y", "width", "height", "visible"]
    }

    ColumnLayout {
        anchors.fill: parent
        spacing: 0

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

            MouseArea {
                id: dragMouseArea
                anchors.fill: parent
                drag.target: root
                drag.threshold: 1
                hoverEnabled: true
            }
        }

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

    Rectangle {
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        width: 10
        height: 10
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

