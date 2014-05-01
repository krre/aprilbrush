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

import QtQuick 2.2
import QtQuick.Window 2.0

Window {
    default property alias content: stack.children
    property var storage

    title: "Untitled"
    flags: Qt.Tool
    width: 200
    height: 200
    color: sysPalette.window
    minimumWidth: 100
    minimumHeight: 100

    onVisibleChanged: {
        if (visible) {
            requestActivate()
        }
    }

    function defaultStorage() {
        return ["x", "y", "width", "height", "visible"]
    }

    SystemPalette {
        id: sysPalette
        colorGroup: SystemPalette.Active
    }

    Item {
        id: stack
        anchors.fill: parent
        anchors.margins: 5
    }
}

