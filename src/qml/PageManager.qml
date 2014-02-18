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
//        width: childrenRect.width
//        height: parent.height
        anchors.fill: parent
        spacing: 5

        Rectangle {
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
//            width: Math.max(count * (currentItem.width + spacing), root.width - 45)
            width: root.width - 45
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
