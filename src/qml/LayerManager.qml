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
    property alias layerView: layerView

    text: "Layers"

    ColumnLayout {
        anchors.fill: parent
        visible: tabView.count > 0

        VerticalList {
            id: layerView
            model: layerModel
            Layout.fillHeight: true
            Layout.fillWidth: true
            onCurrentIndexChanged: if (currentIndex >= 0 ) { currentLayerId = layerModel.get(currentIndex).layerId }
            onCountChanged: if (currentIndex >= 0 ) { currentLayerId = layerModel.get(currentIndex).layerId }
        }

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
                    if (layerView.currentIndex > 0) {
                        layerModel.move(layerView.currentIndex, layerView.currentIndex - 1, 1)
                        undoManager.add(new Undo.raiseLayer())
                    }

                }
            }

            // Down button
            Button {
                Layout.fillWidth: true
                text: qsTr("Down")
                onClicked: {
                    if (layerView.currentIndex < layerView.count - 1) {
                        layerModel.move(layerView.currentIndex, layerView.currentIndex + 1, 1)
                        undoManager.add(new Undo.lowerLayer())
                    }
                }
            }

            // Merge button
            Button {
                Layout.fillWidth: true
                text: qsTr("Merge")
                onClicked: {
                    if ((layerView.count > 1) && (layerView.currentIndex < layerView.count - 1)) {
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
                    undoManager.add(new Undo.deleteLayer(layerView.currentIndex))
                    Utils.deleteLayer(layerView.currentIndex)
                }
            }
        }
    }
}
