import QtQuick 2.0
import "components"
import "utils.js" as Utils
import "undo.js" as Undo

Window {
    id: root
    property alias currentLayerIndex: layersView.currentIndex
    property alias layersView: layersView

    title: "Layers"
    parent: main
    visible: (index == pagesView.currentIndex) && layerManagerVisible
    x: layerManagerPos.x
    y: layerManagerPos.y
    z: 4
    width: layerManagerSize.width
    height: layerManagerSize.height
    autoClose: false
    onReleased: layerManagerPos = Qt.point(x, y)
    onResized: layerManagerSize = Qt.size(width, height)
    onClosed: layerManagerVisible = false
    //onCurrentLayerChanged: console.log("currentLayer: " + currentLayer)

    Column {
        anchors.fill: parent
        width: parent.width
        spacing: 5

        ListView {
            id: layersView
            model: layerModel
            delegate: layerDelegate
            highlight: layerSelected
            highlightMoveDuration: 1

            width: parent.width
            height: root.height - 65

            orientation: ListView.Vertical
            clip: true
            spacing: 4
            onCurrentIndexChanged: if (currentIndex >=0 )currentLayerId = layerModel.get(currentIndex).layerId
        }

        Component {
            id: layerDelegate
            ListItem {
                text: name
                color: ListView.isCurrentItem ? "transparent" : "lightgray"
                closable: ListView.isCurrentItem
                onClicked: { undoManager.add(new Undo.changeLayer(currentLayerIndex, index)); currentLayerIndex = index }
                onClosed: {
                    //undoManager.add(new Undo.deleteLayer(index))
                    Utils.deleteLayer(index)
                }
            }
        }

        Component {
            id: layerSelected
            ListItemComponent {
                width: layersView.width
            }
        }

        // Buttons
        Row {
            id: buttons
            width: parent.width
            height: 20
            spacing: 4

            // New button
            Button {
                width: parent.width / 4 - 4
                height: parent.height
                title: qsTr("New")
                onClicked: {
                    Utils.addLayer()
                    undoManager.add(new Undo.addLayer(currentLayerIndex))
                }
            }
            // Up button
            Button {
                width: parent.width / 4 - 4
                height: parent.height
                title: qsTr("Up")
                onClicked: {
                    if (currentLayerIndex > 0) {
                        layerModel.move(currentLayerIndex, currentLayerIndex - 1, 1)
                        undoManager.add(new Undo.raiseLayer())
                    }

                }
            }
            // Down button
            Button {
                width: parent.width / 4 - 4
                height: parent.height
                title: qsTr("Down")
                onClicked: {
                    if (currentLayerIndex < layersView.count - 1) {
                        layerModel.move(currentLayerIndex, currentLayerIndex + 1, 1)
                        undoManager.add(new Undo.lowerLayer())
                    }
                }
            }
            // Clone button
            Button {
                width: parent.width / 4 - 4
                height: parent.height
                title: qsTr("Clone")
                onClicked: {
                    undoManager.add(new Undo.cloneLayer(canvasArea.pathView.currentItem.pixmap))
                }
            }
        }
    }
}
