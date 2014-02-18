import QtQuick 2.2

Rectangle {
    id: root
    width: 500
    height: 62
    color: "black"
    opacity: 0.8

    ListModel {
        id: pageModel
    }

    Row {
        anchors.centerIn: parent
        spacing: 5

        Rectangle {
            id: plus
            width: 35
            height: 35
            anchors.verticalCenter: parent.verticalCenter
            radius: 10
            antialiasing: true
            color: mouseArea.pressed? "#222222" : mouseArea.containsMouse ? "#474747" : "transparent"
            border.color: "gray"

            Text {
                text: "+"
                anchors.centerIn: parent
                color: "white"
                font.pointSize: 17
                font.bold: true
            }

            MouseArea {
                id: mouseArea
                anchors.fill: parent
                hoverEnabled: true
                onClicked: { pageModel.append({}); pageView.currentIndex = pageView.count - 1 }
            }
        }

        ListView {
            id: pageView
            height: root.height - 6
            width: Math.min(count * (currentItem ? currentItem.width + spacing : 0), root.width - plus.width - 20)
            anchors.verticalCenter: parent.verticalCenter
            model: pageModel
            delegate: pageDelegate
            orientation: ListView.Horizontal
            spacing: 5
            clip: true
        }

        Component {
            id: pageDelegate

            Rectangle {
                width: 100
                height: ListView.view.height
            }
        }
    }
}
