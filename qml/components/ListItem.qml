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

Rectangle {
    id: root
    property alias text: label.text
    property bool closable: true
    signal clicked()
    signal closed()

    width: parent.width
    height: 20
    color: "lightgray"
    border.width: 1
    border.color: "gray"
    radius: 5
    antialiasing: true
    Text {
        id: label
        text: qsTr("Item")
        anchors.verticalCenter: parent.verticalCenter
        anchors.left: parent.left
        anchors.leftMargin: 10
    }
    MouseArea {
        anchors.fill: parent
        onClicked: root.clicked()
    }
    CloseButton {
        visible: closable
        anchors.verticalCenter: parent.verticalCenter
        anchors.right: parent.right
        anchors.rightMargin: 2
        onClicked: closed()
    }
}
