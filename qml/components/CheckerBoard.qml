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

import QtQuick 2.3

Grid {
    property int cellSide: 10
    rows: Math.ceil(height / cellSide)
    columns: Math.ceil(width / cellSide) + (Math.ceil(width / cellSide) % 2 == 1 ? 0 : 1)
    clip: true

    Repeater {
        model: columns * rows

        Rectangle {
            width: cellSide
            height: cellSide
            color: (index % 2 == 0) ? "gray" : "white"
        }
    }
}
