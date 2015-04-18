import QtQuick 2.4
import QtQuick.Controls 1.3
import QtQuick.Layouts 1.1
import QtQuick.Controls.Private 1.0

Rectangle {
    id: root
    property alias title: title.text
    default property alias content: contentArea.children
    implicitWidth: 200
    implicitHeight: 200
    color: mainRoot.sysPalette.window
    border.color: "#5d5d5d"
    Drag.active: mouseArea.drag.active

    MouseArea {
        property point pressedPos
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        width: 30
        height: 30
        hoverEnabled: true

        onPressed: pressedPos = Qt.point(mouseX, mouseY)
        onPositionChanged: {
            if (pressed) {
                root.width = Math.max(root.implicitWidth, root.width + mouse.x - pressedPos.x)
                root.height = Math.max(root.implicitHeight, root.height + mouse.y - pressedPos.y)
            }
        }
    }

    ColumnLayout {
        anchors.fill: parent
        anchors.margins: 5

        Item {
            Layout.fillWidth: true
            Layout.preferredHeight: TextSingleton.implicitHeight * 1.1

            Label {
                id: title
                anchors.centerIn: parent
                text: "Title"
            }

            MouseArea {
                id: mouseArea
                anchors.fill: parent
                drag.target: root
                drag.threshold: 1
            }
        }

        Item {
            id: contentArea
            Layout.fillHeight: true
            Layout.fillWidth: true
        }
    }
}

