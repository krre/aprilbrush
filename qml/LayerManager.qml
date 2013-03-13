import QtQuick 2.0
import "components"
import "utils.js" as Utils

Window {
    id: root
    title: "Layers"
    property int countLayer: 1
    property variant layersModel: pagesModel.count > 0 ? pagesModel.get(pageManager.currentPage).layerSet : 0
    property alias lView: layersView

    Column {
        width: parent.width
        spacing: 5

        ListView {
            id: layersView
            model: layersModel
            delegate: layerDelegate
            highlight: layerSelected
            highlightMoveDuration: 1

            width: parent.width
            height: 120

            orientation: ListView.Vertical
            clip: true
            spacing: 4
        }

        Component {
            id: layerDelegate
            Rectangle {
                width: parent.width
                height: 20
                color: index == layersView.currentIndex ? "transparent" : "lightgray"
                border.width: 1
                border.color: "gray"
                radius: 5
                antialiasing: true
                Text {
                    text: name
                    anchors.verticalCenter: parent.verticalCenter
                    anchors.left: parent.left
                    anchors.leftMargin: 10
                }
                MouseArea {
                    anchors.fill: parent
                    onClicked: {
                        layersView.currentIndex = index
                        //layersModel.get(layersView.currentIndex).active = layersView.currentIndex
                        //layersModel.setProperty(layersView.currentIndex, "active", layersView.currentIndex)
                        //layersModel.set(layersView.currentIndex, { active: layersView.currentIndex })
                        brush.setLayer(layersModel.get(layersView.currentIndex).number)
                    }
                }
                CloseButton {
                    anchors.verticalCenter: parent.verticalCenter
                    anchors.right: parent.right
                    anchors.rightMargin: 2
                    onClicked: {
                        layersModel.remove(index)
                        if (layersModel.count > 0) brush.setLayer(layersModel.get(layersView.currentIndex).number);
                    }
                }
            }
        }

        Component {
            id: layerSelected
            Rectangle {
                width: layersView.width
                height: 20
                border.width: 1
                border.color: "gray"
                radius: 5
                antialiasing: true
                color: "white"
            }
        }

        // Buttons
        Row {
            width: parent.width
            height: 20
            spacing: 4

            // New button
            Button {
                width: parent.width / 4 - 4
                height: parent.height
                text: qsTr("New")
                onClicked: {
                    var numNextLayer = Utils.zeroFill(countLayer + 1, 2)
                    if (layersView.currentIndex < 0)
                        layersView.currentIndex = 0
                    layersModel.insert(layersView.currentIndex, {
                                           name: "Layer-" + numNextLayer,
                                           number: ++countLayer,
                                           colorImage: "transparent",
                                           enable: true })
                    layersView.decrementCurrentIndex()
                }
            }
            // Up button
            Button {
                width: parent.width / 4 - 4
                height: parent.height
                text: qsTr("Up")
                onClicked: {
                    if (layersView.currentIndex > 0)
                        layersModel.move(layersView.currentIndex, layersView.currentIndex - 1, 1)
                }
            }
            // Down button
            Button {
                width: parent.width / 4 - 4
                height: parent.height
                text: qsTr("Down")
                onClicked: {
                    if (layersView.currentIndex < layersView.count - 1)
                        layersModel.move(layersView.currentIndex, layersView.currentIndex + 1, 1)
                }
            }
            // Clone button
            Button {
                width: parent.width / 4 - 4
                height: parent.height
                text: qsTr("Clone")
                onClicked: {
                    console.log("Clone layer")
                }
            }
        }
    }
}
