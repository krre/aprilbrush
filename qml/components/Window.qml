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
    id: root
    property string title: "Unnamed"
    default property alias content: stack.children
    property int defaultWidth: 200
    property int defaultHeight: 200
    property int indent: 10
    property bool autoClose: true // used for disabling automatic closing window

    signal released
    signal closed
    signal resized

    width: defaultWidth
    height: defaultHeight

    MouseArea {
        anchors.fill: parent
        drag.target: parent
        preventStealing: true
        hoverEnabled: true
        onPressed: {
            // Moving a item on top of the scene
            var maxZ = 0
            for (var i = 0; i < root.parent.children.length; i++)
                if (root.parent.children[i].z > maxZ) maxZ = root.parent.children[i].z
            root.z = ++maxZ
        }
        onReleased: root.released()
    }

    Rectangle {
        id: rect
        anchors.fill: parent
        color: "#eeeeee"
        border.color: "gray"
        radius: 7
        antialiasing: true

        Column {
            // Header
            Item {
                id: head;
                width: rect.width;
                height: 25
                Text {
                    anchors.left: parent.left
                    anchors.verticalCenter: parent.verticalCenter
                    anchors.margins: indent
                    text: title
                    font.pointSize: 9
                    //font.bold: true

                }
            }
            // Content stack
            Item {
                id: stack
                width: rect.width - indent * 2;
                height: rect.height - head.height - indent * 1.5
                anchors.horizontalCenter: parent.horizontalCenter
            }
        }

        CloseButton {
            anchors.top: parent.top
            anchors.right: parent.right
            onClicked: autoClose ? root.visible = false : root.closed()
        }

        // Resize handler
        Item {
            id: resizeHandler
            width: 20
            height: 20
            anchors.bottom: parent.bottom
            anchors.right: parent.right
            Text {
                text: "="
                anchors.centerIn: parent
                font.pointSize: 11
                font.bold: resizeMouseArea.containsMouse ? true : false
            }

            MouseArea {
                id: resizeMouseArea
                property bool grabFlag: false
                anchors.fill: parent
                hoverEnabled: true
                onPressed: grabFlag = true
                onReleased: { grabFlag = false; root.resized() }
                onPositionChanged: {
                    if (grabFlag) {
                        var newWidth = root.width + mouseX - indent
                        root.width = newWidth < defaultWidth ? defaultWidth : newWidth
                        var newHeight = root.height + mouseY - indent
                        root.height = newHeight < defaultHeight ? defaultHeight : newHeight
                    }
                }
            }
        }
    }

    Shadow {
        surface: rect
    }
}
