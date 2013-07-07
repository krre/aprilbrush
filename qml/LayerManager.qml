/* AprilBrush - Digital Painting Software
 * Copyright (C) 2012-2013 Vladimir Zarypov <krre@mail.ru>
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation;
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 */

import QtQuick 2.1
import "components"
import "utils.js" as Utils
import "undo.js" as Undo

Window {
    id: root
    property alias currentLayerIndex: layersView.currentIndex
    property alias layersView: layersView

    title: "Layers"
    autoClose: false
    // TODO: fix binding to settings property
    /*
    x: settings.layerManager.position.x
    y: settings.layerManager.position.y
    z: settings.layerManager.position.z
    width: settings.layerManager.size.width
    height: settings.layerManager.size.height
    visible: (index == pagesView.currentIndex) && settings.layerManager.visible
    */

    x: layerManagerPos.x
    y: layerManagerPos.y
    z: layerManagerPos.z
    width: layerManagerSize.width
    height: layerManagerSize.height
    visible: (index == pagesView.currentIndex) && layerManagerVisible

    onReleased: {
        layerManagerPos = Qt.vector3d(x, y, z)
    }
    onResized: {
        layerManagerSize = Qt.size(width, height)
    }
    onClosed: layerManagerVisible = false

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
            onCurrentIndexChanged: if (currentIndex >=0 ) currentLayerId = layerModel.get(currentIndex).layerId
            onCountChanged: if (currentIndex >=0 ) currentLayerId = layerModel.get(currentIndex).layerId
        }

        Component {
            id: layerDelegate
            ListItem {
                text: name
                color: ListView.isCurrentItem ? "transparent" : "lightgray"
                onClicked: {
                    undoManager.add(new Undo.changeLayer(currentLayerIndex, index));
                    currentLayerIndex = index
                }
                onClosed: {
                    undoManager.add(new Undo.deleteLayer(index))
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
                width: parent.width / 5 - 4
                height: parent.height
                title: qsTr("New")
                onClicked: {
                    Utils.addLayer()
                    undoManager.add(new Undo.addLayer())
                }
            }
            // Up button
            Button {
                width: parent.width / 5 - 4
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
                width: parent.width / 5 - 4
                height: parent.height
                title: qsTr("Down")
                onClicked: {
                    if (currentLayerIndex < layersView.count - 1) {
                        layerModel.move(currentLayerIndex, currentLayerIndex + 1, 1)
                        undoManager.add(new Undo.lowerLayer())
                    }
                }
            }

            // Merge button
            Button {
                width: parent.width / 5 - 4
                height: parent.height
                title: qsTr("Merge")
                onClicked: {
                    if ((layersView.count > 1) && (currentLayerIndex < layersView.count - 1)) {
                        undoManager.add(new Undo.mergeLayer())
                    }
                }
            }

            // Clone button
            Button {
                width: parent.width / 5 - 4
                height: parent.height
                title: qsTr("Clone")
                onClicked: {
                    undoManager.add(new Undo.cloneLayer())
                }
            }
        }
    }
}
