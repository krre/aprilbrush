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
import "../main"

Window {
    default property alias content: stack.children
    property var storage
    property real relativeX: 0
    property real relativeY: 0

    title: "Untitled"
    flags: Qt.Tool
    x: mainRoot.x + relativeX
    y: mainRoot.y + relativeY
    width: 200
    height: 200
    color: mainRoot.sysPalette.window
    minimumWidth: 100
    minimumHeight: 100

    onVisibleChanged: {
        if (visible) {
            requestActivate()
        }
    }
    onXChanged: relativeX = x - mainRoot.x
    onYChanged: relativeY = y - mainRoot.y

    function defaultStorage() {
        return ["relativeX", "relativeY", "width", "height", "visible"]
    }

    Actions { id: actions}

    Item {
        id: stack
        anchors.fill: parent
        anchors.margins: 5
    }
}

