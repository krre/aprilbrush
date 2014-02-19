/* AprilBrush - Digital Painting Software
 * Copyright (C) 2012-2014 Vladimir Zarypov <krre31@gmail.com>
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
    property alias currentRow: layerView.currentIndex
    property var layerModel: currentPageIndex > 0 ? mainModel.get(currentPageIndex).layerModel : []

    title: "Layers"
    objectName: "layerManager"
    storage: { var list = defaultStorage(); return list }

    function addLayer() {

}

    ColumnLayout {
        anchors.fill: parent

        VerticalList {
            id: layerView
            model: layerModel
            Layout.fillHeight: true
            Layout.fillWidth: true
            onCurrentIndexChanged: if (currentIndex >= 0 ) { currentLayerId = layerModel.get(currentIndex).layerId }
            onCountChanged: if (currentIndex >= 0 ) { currentLayerId = layerModel.get(currentIndex).layerId }
        }

        RowLayout {
            spacing: 2

            Button {
                Layout.fillWidth: true
                text: qsTr("New")
                onClicked: {
                    addLayer()
//                    undoManager.add(new Undo.addLayer())
                }
            }

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

            Button {
                Layout.fillWidth: true
                text: qsTr("Merge")
                onClicked: {
                    if ((layerView.count > 1) && (layerView.currentIndex < layerView.count - 1)) {
                        undoManager.add(new Undo.mergeLayer())
                    }
                }
            }

            Button {
                Layout.fillWidth: true
                text: qsTr("Clone")
                onClicked: {
                    undoManager.add(new Undo.cloneLayer())
                }
            }
        }
    }
}
