import QtQuick 2.0
import "components"
import "utils.js" as Utils

Window {
    id: root
    title: "Layers"
    //property int countLayer: 1
    //property variant layersModel: pagesModel.count > 0 ? pagesModel.get(pageManager.currentPage).layerSet : 0
    property alias currentLayer: layersView.currentIndex

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
                //hash:
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
                        var hashPageLayer = pagesModel.get(currentPage).hash * 1000 + layersModel.get(currentLayer).hash
                        brush.setLayer(hashPageLayer);
                        //console.log(hashPageLayer)
                    }
                }
                CloseButton {
                    anchors.verticalCenter: parent.verticalCenter
                    anchors.right: parent.right
                    anchors.rightMargin: 2
                    onClicked: {
                        console.log("index before " + index)
                        layersModel.remove(index)
                        var i = 0
                        //while (index == -1)
                        //    i++
                        console.log(i)
                        console.log("index after " + index)
                        var hashPageLayer = pagesModel.get(currentPage).hash * 1000 + layersModel.get(index).hash

                        if (layersModel.count > 0) brush.setLayer(hashPageLayer);
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
                    var maxNumLayer = 0;
                    for (var layer = 0; layer < layersModel.count; layer++)
                        if (layersModel.get(layer).hash > maxNumLayer) maxNumLayer = layersModel.get(layer).hash
                    maxNumLayer++
                    var numNextLayer = Utils.zeroFill(maxNumLayer, 3)

                    if (currentLayer < 0)
                        currentLayer = 0
                    layersModel.insert(currentLayer, {
                                           name: "Layer-" + numNextLayer,
                                           hash: maxNumLayer,
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
