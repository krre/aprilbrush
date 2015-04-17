import QtQuick 2.4
import QtQuick.Controls 1.3
import QtQuick.Layouts 1.1
import QtQuick.Controls.Private 1.0

Rectangle {
    property alias title: title.text
    default property alias content: contentArea.children
    width: 200
    height: 200
    color: mainRoot.sysPalette.window
    border.color: "#5d5d5d"
    radius: 5
    antialiasing: true
    Drag.active: mouseArea.drag.active
    Drag.hotSpot.x: 10
    Drag.hotSpot.y: 10

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
        }

        Item {
            id: contentArea
            Layout.fillHeight: true
            Layout.fillWidth: true
        }
    }

    MouseArea {
        id: mouseArea
        anchors.fill: parent
        drag.target: parent
    }
}

