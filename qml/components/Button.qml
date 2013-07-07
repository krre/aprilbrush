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

Rectangle {
    id: root
    property alias title: label.text
    signal clicked()

    width: 50
    height: 20
    color: "lightgray"
    radius: 5
    antialiasing: true
    Text {
        id: label
        text: qsTr("Button")
        anchors.centerIn: parent
    }
    MouseArea {
        anchors.fill: parent
        onClicked: root.clicked()
    }
}
