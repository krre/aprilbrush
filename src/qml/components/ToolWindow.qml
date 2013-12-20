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
import QtQuick.Layouts 1.1

Rectangle {
    id: root
    property alias text: title.text
    default property alias content: stack.children
    property int defaultSize: 100
    property int indent: 5
    property color backgroundColor: sysPalette.window

    Layout.minimumWidth: defaultSize
    Layout.minimumHeight: defaultSize

    SystemPalette {
        id: sysPalette
        colorGroup: SystemPalette.Active
    }
    color: backgroundColor

    ColumnLayout {
        anchors.fill: parent
        spacing: 0

        Rectangle {
            Layout.preferredWidth: parent.width
            height: 25
            color: sysPalette.window

            Text {
                id: title
                x: 10
                anchors.verticalCenter: parent.verticalCenter
                text: qsTr("title")
            }

        }

        Item {
            Layout.preferredWidth: parent.width
            Layout.fillHeight: true

            // Content stack
            Item {
                id: stack
                width: parent.width - indent * 2;
                height: parent.height - indent
                anchors.horizontalCenter: parent.horizontalCenter
                Layout.fillHeight: true
            }
        }
    }
}
