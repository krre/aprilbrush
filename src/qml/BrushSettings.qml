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

import QtQuick 2.1
import QtQuick.Controls 1.1
import "components"
import "settings.js" as Settings

ToolWindow {
    id: root
    title: qsTr("Brush Settings")
    property alias brushModel: brushModel
    property alias diameter: diameter.value
    property alias opaque: opaque.value
    property alias hardness: hardness.value
    property alias spacing: spacing.value

    objectName: "brushSettings"
    storage: {
        var list = defaultStorage()
        list.push("diameter", "opaque", "hardness", "spacing")
        return list
    }

    signal settingsChanged()

    ListView {
        anchors.fill: parent
        model: brushModel
        clip: true
        spacing: 7

        VisualItemModel {
            id: brushModel
            SliderText { id: diameter; title: qsTr("Diameter"); width: parent.width; minimumValue: 1; maximumValue: 100; value: 20; onValueChanged: root.settingsChanged() }
            SliderText { id: opaque; title: qsTr("Opaque"); width: parent.width; value: 85; onValueChanged: root.settingsChanged() }
            SliderText { id: hardness; title: qsTr("Hardness"); width: parent.width; minimumValue: 1; value: 95; onValueChanged: root.settingsChanged() }
            SliderText { id: spacing; title: qsTr("Spacing"); width: parent.width; minimumValue: 5; maximumValue: 200; value: 25; onValueChanged: root.settingsChanged() }
        }
    }
}

