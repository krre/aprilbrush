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

Item {
    id: name
    width: 500
    height: 62

    Rectangle {
        id: rect
        anchors.fill: parent
        radius: 10
        antialiasing: true
        border.color: "gray"
        color: "#f5f5f5"

        MouseArea {
            anchors.fill: parent
            hoverEnabled: true
        }

        Row {
            height: parent.height
            width: childrenRect.width
            anchors.centerIn: parent
            spacing: 5

            DockItem {
                name: brushSettings.title
                onClicked: brushSettings.visible = !brushSettings.visible
            }

            DockItem {
                name: "Layers" // TODO: bind on layerManager object
                onClicked: layerManagerVisible = !layerManagerVisible
            }

            DockItem {
                name: "Color"
                onClicked: colorPicker.visible = !colorPicker.visible
            }

            DockItem {
                name: "Undo History" // TODO: bind on undoManager object
                onClicked: undoManagerVisible = !undoManagerVisible

            }

            DockItem {
                name: brushLibrary.title
                onClicked: brushLibrary.visible = !brushLibrary.visible
            }
        }
    }

    Shadow {
        surface: rect

    }
}
