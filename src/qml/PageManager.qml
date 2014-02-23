import QtQuick 2.2
import QtQuick.Controls 1.0
import "components"
import "style"
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

        layerManager.addLayer("Background", "white")
        layerManager.addLayer("Layer", "transparent")
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

        Button {
            id: plus
            width: 35
            height: 35
            anchors.verticalCenter: parent.verticalCenter
            text: "+"
            style: ButtonStyle {}
            onClicked: addPage()
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

            Rectangle {
                property alias canvas: canvas
                width: 100
                height: ListView.view.height
                opacity: ListView.isCurrentItem ? 1.0 : 0.6
                color: "transparent"
                border.color: "gray"

                Canvas {
                    id: canvas
                    width: parent.width - 2
                    height: parent.height - 2
                    anchors.centerIn: parent

                    function paintThumbnail() {
                        var ctx = getContext("2d")
                        ctx.clearRect(0, 0, width, height)
                        var thumbnail = canvasView.currentItem.currentItem.getContext("2d").getImageData(0, 0, imageSize.width, imageSize.height)
                        ctx.drawImage(thumbnail, 0, 0, width, height)
                        requestPaint()
                    }

                    MouseArea {
                        anchors.fill: parent
                        onClicked: {
                            pageView.currentIndex = index
                        }
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
}
