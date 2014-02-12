/* AprilBrush - Digital Painting Software
 * Copyright (C) 2012-2013 Vladimir Zarypov <krre31@gmail.com>
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
import QtQuick.Layouts 1.1
import QtQuick.Controls 1.1
import QtQuick.Controls.Styles 1.1

Rectangle {
    id: root
    property alias text: title.text
    default property alias content: stack.children
    property int indent: 5
    property bool collapse: false
    property int stashHeight: height

    Layout.minimumHeight: collapse ? header.height + 4 : 200
    Layout.minimumWidth: 200

    width: 200
    height: 200

    color: palette.toolBgColor

    onCollapseChanged: if (collapse) {
                           stashHeight = height
                           root.Layout.maximumHeight = header.height + 4
                       } else {
                           root.Layout.maximumHeight = -1
                           height = stashHeight
                       }


    ColumnLayout {
        anchors.fill: parent
        spacing: 0

        Rectangle {
            height: 2
            Layout.preferredWidth: parent.width
            color: palette.borderColor
        }

        Rectangle {
            id: header
            Layout.preferredWidth: parent.width
            height: 20
            gradient: Gradient {
                GradientStop { position: 0.0; color: palette.toolHeaderColor1 }
                GradientStop { position: 1.0; color: palette.toolHeaderColor2 }
            }

            Row {
                spacing: 2

                Image {
                    source: "../../images/triangle.png"
                    scale: 0.7
                    rotation: collapse ? 0 : 90
                    MouseArea {
                        anchors.fill: parent
                        onClicked: collapse = !collapse
                    }
                }

                Text {
                    id: title
                    x: 10
                    anchors.verticalCenter: parent.verticalCenter
                    text: qsTr("title")
                    color: "white"
                }
            }
        }

        Rectangle {
            height: 2
            Layout.preferredWidth: parent.width
            color: palette.borderColor
        }

        Rectangle {
            id: contentContainer
            Layout.preferredWidth: parent.width
            Layout.fillHeight: true
            color: palette.toolBgColor
            visible: !collapse

            // Content stack
            Item {
                id: stack
                width: parent.width - indent * 2;
                height: parent.height - indent * 2
                anchors.centerIn: parent
            }
        }
    }
}
