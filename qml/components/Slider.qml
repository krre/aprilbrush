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

Item {
    property string name: "Slider"
    property int min: 0
    property int max: 100
    property int init: min + (max - min) / 2
    property int value: min + (max - min) * (handle.x / (scale.width - handle.width))
    property int valueX: 0

    Component.onCompleted: valueX = init
    onInitChanged: valueX = init

    width: parent.width
    onWidthChanged: valueX = value
    height: 30

    Item {
        height: 10
        width: parent.width

        Text {
            text: name
            anchors.left: parent.left
            anchors.margins: 5
        }
        Text {
            text: value
            anchors.right: parent.right
            anchors.margins: 5
        }
    }
    // Scale
    Item {
        id: scale
        height: 12
        width: parent.width
        anchors.bottom: parent.bottom
        Rectangle {
            width: parent.width
            height: parent.height
            radius: 5
            antialiasing: true
            border.color: "gray"
        }
        // Handler
        Rectangle {
            id: handle
            x: (valueX - min) / (max - min) * (scale.width - width)
            width: 20
            height: parent.height
            radius: 5
            antialiasing: true
            color: "gray"
            MouseArea {
                anchors.fill: parent
                preventStealing: true
                drag {
                    target: parent
                    axis: Drag.XAxis
                    minimumX: 0
                    maximumX: scale.width - parent.width
                }
            }
        }
    }
}
