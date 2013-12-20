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
import QtQuick.Window 2.0

Item {
//    title: "Unnamed"
    default property alias content: stack.children
    property int defaultSize: 200
    property int indent: border ? 10 : 0
    property color backGroundColor: sysPalette.window
    property bool border: true

//    minimumWidth: defaultSize
//    minimumHeight: defaultSize
//    flags: Qt.Tool
    SystemPalette {
        id: sysPalette
        colorGroup: SystemPalette.Active
    }
//    color: backGroundColor

    // Content stack
    Item {
        id: stack
        width: parent.width - indent * 2;
        height: parent.height - indent * 2
        anchors.centerIn: parent
    }
}
