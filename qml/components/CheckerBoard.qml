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

import QtQuick 2.0

Item {
    id: root
    property int cellSide: 10
    width: 100
    height: 100

    Rectangle {
    id: rect
    anchors.fill: parent

        Grid {
            id: grid
            anchors.fill: parent
            rows: parent.height / cellSide + (index % 2 == 0 ? 2 : 1)
            columns: parent.width / cellSide + (index % 2 == 0 ? 2 : 1)
            clip: true
            Repeater {
                model: grid.columns * grid.rows
                Rectangle {
                    width: root.cellSide
                    height: root.cellSide
                    color: (index % 2 == 0) ? "gray" : "white"
                }
            }
        }
    }

    Shadow {
        surface: rect
    }
}



