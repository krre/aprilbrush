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
    signal clicked
    property string name: "Unnamed"

    width: 55
    height: 55
    anchors.verticalCenter: parent.verticalCenter

    Rectangle {
        radius: 5
        anchors.fill: parent
        antialiasing: true
        color: mouseArea.pressed ? "#cccccc" : "#e6e6e6"
        border.color: "gray"
    }

    Text {
        text: name
        anchors.fill: parent
        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter
        wrapMode: Text.WordWrap
        clip: true
    }

    MouseArea {
        id: mouseArea
        anchors.fill: parent
        onReleased: root.clicked()
    }
}
