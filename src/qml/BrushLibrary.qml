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
import "brushlib.js" as BrushLib

ToolWindow {
    id: root
//    title: "Brush Library"

    Item {
        anchors.fill: parent

        GridView {
            id: libraryView
            model: libraryModel
            delegate: brushDelegate

            width: parent.width
            height: parent.height
            cellWidth: 56
            cellHeight: 56
            highlight: brushSelected
            highlightMoveDuration: 1
            clip: true
            Component.onCompleted: {
                BrushLib.loadBrushPack()
                brushSettings.size.value = libraryModel.get(0).size
                brushSettings.opaque.value = libraryModel.get(0).opaque
                brushSettings.spacing.value = libraryModel.get(0).spacing
                brushSettings.hardness.value = libraryModel.get(0).hardness
                brushSettings.roundness.value = libraryModel.get(0).roundness
                brushSettings.angle.value = libraryModel.get(0).angle
                brushSettings.jitter.value = libraryModel.get(0).jitter
            }
        }

        Component {
            id: brushDelegate
            ListItem {
                text: name
                width: 50
                height: 50
                closable: false
                color: GridView.isCurrentItem ? "transparent" : "lightgray"
                onClicked: {
                    libraryView.currentIndex = index
                    brushSettings.size.value = size
                    brushSettings.opaque.value = opaque
                    brushSettings.spacing.value = spacing
                    brushSettings.hardness.value = hardness
                    brushSettings.roundness.value = roundness
                    brushSettings.angle.value = angle
                    brushSettings.jitter.value = jitter
                }
            }
        }

        Component {
            id: brushSelected
            ListItemComponent {
                width: 50
                height: 50
            }
        }

        ListModel {
            id: libraryModel
        }
    }
}
