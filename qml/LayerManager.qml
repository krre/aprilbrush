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
import QtQuick.Controls 1.0
import QtQuick.Layouts 1.0
import "components"
import "utils.js" as Utils
import "undo.js" as Undo

ToolWindow {
    id: root
    property alias currentLayerIndex: layersView.currentRow
    property alias layersView: layersView

    title: "Layers"
    border: false

    ColumnLayout {
        anchors.fill: parent

        TableView {
            id: layersView
            Layout.fillWidth: true
            Layout.fillHeight: true
            headerVisible: false
            model: layerModel
//            currentRow: 0
            onActivated: console.log("activated " + row)
            onClicked: console.log("clicked " + row)

            TableViewColumn {
                delegate: Component {
                    Text {
                        text: name
                        anchors.leftMargin: 10
                    }
                }
            }
        }

/*
        ListView {
            id: layersView
            model: layerModel
            delegate: layerDelegate
            highlight: layerSelected
            highlightMoveDuration: 1

            Layout.fillWidth: true
            Layout.fillHeight: true

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
*/
        // Buttons
        RowLayout {
            spacing: 2

            // New button
            Button {
                Layout.fillWidth: true
                text: qsTr("New")
                onClicked: {
                    Utils.addLayer()
                    undoManager.add(new Undo.addLayer())
                }
            }
            // Up button
            Button {
                Layout.fillWidth: true
                text: qsTr("Up")
                onClicked: {
                    if (currentLayerIndex > 0) {
                        layerModel.move(currentLayerIndex, currentLayerIndex - 1, 1)
                        undoManager.add(new Undo.raiseLayer())
                    }

                }
            }
            // Down button
            Button {
                Layout.fillWidth: true
                text: qsTr("Down")
                onClicked: {
                    if (currentLayerIndex < layersView.count - 1) {
                        layerModel.move(currentLayerIndex, currentLayerIndex + 1, 1)
                        undoManager.add(new Undo.lowerLayer())
                    }
                }
            }

            // Merge button
            Button {
                Layout.fillWidth: true
//                Layout.fillHeight: true
//                Layout.maximumHeight: parent.height
                text: qsTr("Merge")
                onClicked: {
                    if ((layersView.count > 1) && (currentLayerIndex < layersView.count - 1)) {
                        undoManager.add(new Undo.mergeLayer())
                    }
                }
            }

            // Clone button
            Button {
                Layout.fillWidth: true
                text: qsTr("Clone")
                onClicked: {
                    undoManager.add(new Undo.cloneLayer())
                }
            }

            // Delete button
            Button {
                Layout.fillWidth: true
                text: qsTr("Delete")
                onClicked: {
                    console.log("delete layer" + layersView.currentRow)
//                    undoManager.add(new Undo.deleteLayer(layersView.currentRow))
                }
            }
        }
    }
}
