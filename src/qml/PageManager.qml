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
import QtGraphicalEffects 1.0
import "components"
import "utils.js" as Utils

Item {
    property alias pagesView: pagesView

    width: 600
    height: 34

    Rectangle {
        id: rect
        color: "#eeeeee"
        border.color: "gray"
        radius: 7
        antialiasing: true
        anchors.fill: parent
        // Uses for correctly change cursor shape
        MouseArea {
            anchors.fill: parent
            hoverEnabled: true
        }

        Row {
            anchors.fill: parent
            // Button for adding page
            Item {
                id: addPageArea
                width: 30
                height: parent.height
                Text {
                    text: "+"
                    font.bold: true
                    font.pixelSize: 15
                    anchors.centerIn: parent
                }
                MouseArea {
                    anchors.fill: parent
                    onClicked: Utils.addPage()
                }
            }

            ListView {
                id: pagesView
                model: pageModel
                delegate: pagesDelegate
                highlight: pageSelected
                highlightMoveDuration: 1

                height: parent.height - 8
                width: parent.width - addPageArea.width - helpArea.width - 10
                anchors.verticalCenter: parent.verticalCenter
                orientation: ListView.Horizontal
                spacing: 5
                clip: true                
                onCurrentIndexChanged: {
                    if (currentIndex >= 0) {
                        var layerIndex = pagesView.currentItem.layerManager.currentLayerIndex
                        if (layerIndex >= 0)
                            currentLayerId = pageModel.get(currentIndex).layerModel.get(layerIndex).layerId
                    }
                }
                Component.onCompleted: Utils.addPage()
            }

            Component {               
                id: pagesDelegate
                ListItem {
                    property alias undoManager: undoManager
                    property alias layerManager: layerManager
                    property alias canvasArea: canvasArea

                    width: 100
                    height: pagesView.height
                    color: ListView.isCurrentItem ? "transparent" : "lightgray"
                    text: name
                    onClicked: { pagesView.currentIndex = index }
                    onClosed: Utils.deletePage(index)
                }
            }

            Component {
                id: pageSelected
                ListItemComponent {
                    width: 100
                    height: pagesView.height
                }
            }

            Item {
                id: helpArea
                width: 15
                height: parent.height
                Text {
                    text: "?"
                    font.pixelSize: 15
                    anchors.fill: parent
                    horizontalAlignment: Text.AlignHCenter
                    verticalAlignment: Text.AlignVCenter
                }
                MouseArea {
                    anchors.fill: parent
                    onClicked: aboutWindow.visible = true
                }

            }
        }
    }
}
