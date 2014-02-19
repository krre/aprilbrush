import QtQuick 2.2
import "components"
import "settings.js" as Settings

Item {
    id: root
    property alias pageView: pageView
    width: 500
    height: collapse ? 0 : implicitHeight
    implicitHeight: 62
    property bool collapse: false

    objectName: "pageManager"
    property var storage: ["collapse"]

    Component.onCompleted: addPage()

    function addPage() {
        mainModel.append({ layerModel: []})
        pageView.currentIndex = pageView.count - 1
    }

    Rectangle {
        anchors.fill: parent
        color: "black"
        opacity: 0.8
        MouseArea {
            anchors.fill: parent
        }
    }

    Row {
        visible: !collapse
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
                onClicked: addPage()
            }
        }

        ListView {
            id: pageView
            height: root.height - 6
            width: Math.min(count * (currentItem ? currentItem.width + spacing : 0), root.width - plus.width - 20)
            anchors.verticalCenter: parent.verticalCenter
            model: mainModel
            delegate: pageDelegate
            orientation: ListView.Horizontal
            spacing: 5
            clip: true
        }

        Component {
            id: pageDelegate

            Canvas {
                width: 100
                height: ListView.view.height
                opacity: ListView.isCurrentItem ? 1.0 : 0.6

                function paintThumbnail() {
                    var ctx = getContext("2d")
                    ctx.clearRect(0, 0, width, height)
                    var thumbnail = canvasView.currentItem.getContext("2d").getImageData(0, 0, imageSize.width, imageSize.height)
                    ctx.drawImage(thumbnail, 0, 0, width, height)
                    requestPaint()
                }

                MouseArea {
                    anchors.fill: parent
                    onClicked: parent.ListView.view.currentIndex = index
                }

                CloseButton {
                    anchors.top: parent.top
                    anchors.topMargin: 5
                    anchors.right: parent.right
                    anchors.rightMargin: 5
                    onClicked: mainModel.remove(index)
                }
            }
        }
    }
}
