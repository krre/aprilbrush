import QtQuick 2.0
import "components"
import "utils.js" as Utils

Window {
    id: root
    title: "Layers"
    property alias currentLayer: layersView.currentIndex
    property alias layerView: layersView

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
                color: index == currentLayer ? "transparent" : "lightgray"
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
                        currentLayer = index
                        var hashPageLayer = pagesModel.get(currentPage).hashPage * 1000 + hashLayer
                        brush.setLayer(hashPageLayer);
                    }
                }
                CloseButton {
                    anchors.verticalCenter: parent.verticalCenter
                    anchors.right: parent.right
                    anchors.rightMargin: 2
                    onClicked: {
                        var hashPageLayer = pagesModel.get(currentPage).hashPage * 1000 + hashLayer
                        layersModel.remove(index)
                        brush.deleteLayer(hashPageLayer)
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
                    if (currentPage < 0)
                        return
                    var maxNumLayer = 0;
                    for (var layer = 0; layer < layersModel.count; layer++)
                        if (layersModel.get(layer).hashLayer > maxNumLayer) maxNumLayer = layersModel.get(layer).hashLayer
                    maxNumLayer++
                    var numNextLayer = Utils.zeroFill(maxNumLayer, 3)

                    if (currentLayer < 0)
                        currentLayer = 0
                    layersModel.insert(currentLayer, {
                                           name: "Layer-" + numNextLayer,
                                           hashLayer: maxNumLayer,
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
                    if (currentLayer > 0)
                        layersModel.move(currentLayer, currentLayer - 1, 1)
                }
            }
            // Down button
            Button {
                width: parent.width / 4 - 4
                height: parent.height
                text: qsTr("Down")
                onClicked: {
                    if (currentLayer < layersView.count - 1)
                        layersModel.move(currentLayer, currentLayer + 1, 1)
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
