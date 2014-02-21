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

Item {
    id: root
    property alias title: title.text
    default property alias content: stack.children
    property int indent: 10
    property int headerHeight: 30
    property bool collapse: false
    property real currentHeight: implicitHeight
    property var storage

    implicitWidth: 200
    implicitHeight: 200

    function defaultStorage() {
        return ["x", "y", "z", "width", "height", "currentHeight", "collapse", "visible"]
    }

    Rectangle {
        anchors.fill: parent
        opacity: 0.8
        border.color: "black"
        radius: 5
        antialiasing: true
        gradient: Gradient {
            GradientStop { position: 0.0; color: "gray" }
            GradientStop { position: headerHeight / height; color: "black" }
            GradientStop { position: 1.0; color: "black" }
        }
    }

    MouseArea {
        anchors.fill: parent
        drag.target: root
        preventStealing: true
        hoverEnabled: true
        onPressed: {
            // Moving a item on top of the scene
            var maxZ = 0
            for (var i = 0; i < root.parent.children.length; i++)
                if (root.parent.children[i].z > maxZ) {
                    maxZ = root.parent.children[i].z
                }
            root.z = ++maxZ
        }
    }

    Row {
        anchors.left: parent.left
        anchors.leftMargin: 2
        anchors.top: parent.top
        anchors.topMargin: 8
        spacing: 2

        Image {
            y: -2
            source: "../../images/triangle.png"
            scale: 0.6
            rotation: collapse ? 0 : 90
            MouseArea {
                anchors.fill: parent
                onClicked: {
                    collapse = !collapse
                    root.height = collapse ? headerHeight: currentHeight
                }
            }
        }

        Text {
            id: title
            text: qsTr("Untitled")
            color: "white"
        }
    }

    CloseButton {
        id: closeButton
        anchors.top: parent.top
        anchors.topMargin: 5
        anchors.right: parent.right
        anchors.rightMargin: 5
        onClicked: root.visible = false
    }

    // Content stack
    Item {
        id: stack
        width: parent.width - indent * 2
        height: parent.height - headerHeight - indent
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.bottom: parent.bottom
        anchors.bottomMargin: indent
        visible: !collapse
    }

    // Resize handler
    Item {
        id: resizeHandler
        width: 20
        height: 20
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 2
        anchors.right: parent.right
        visible: !collapse

        Text {
            property color activeColor: Qt.darker("white", 1.1)
            text: ".."
            anchors.centerIn: parent
            font.pointSize: 15
            color: resizeMouseArea.pressed ? Qt.darker(activeColor, 1.2) : resizeMouseArea.containsMouse ? activeColor : "#9c9494"
        }

        MouseArea {
            id: resizeMouseArea
            property bool resizeMode: false
            anchors.fill: parent
            hoverEnabled: true
            onPressed: resizeMode = true
            onReleased: { resizeMode = false }
            onPositionChanged: {
                if (resizeMode) {
                    var newWidth = root.width + mouseX - indent
                    root.width = newWidth < root.implicitWidth ? root.implicitWidth : newWidth
                    var newHeight = root.height + mouseY - indent
                    currentHeight = newHeight < root.implicitWidth ? root.implicitWidth : newHeight
                    root.height = currentHeight
                }
            }
        }
    }
}

