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
import QtQuick.Controls 1.0
import "components"

ToolWindow {
    id: root
    title: "Brush Settings"

    property alias size: sizeSlider
    property alias opaque: opacitySlider
    property alias spacing: spacingSlider
    property alias hardness: hardnessSlider
    property alias roundness: roundnessSlider
    property alias angle: angleSlider
    property alias jitter: jitterSlider

    Item {
        id: sliders
        anchors.fill: parent

        VisualItemModel {
            id: brushSettingsModel
            Item {
                height: 14
                width: sliders.width
                Label { text: qsTr("Size"); anchors.left: parent.left }
                Label { text: Math.round(sizeSlider.value); anchors.right: parent.right }
            }
            Slider { id: sizeSlider; width: sliders.width; minimumValue: 1; maximumValue: 200 }
            Item {
                height: 14
                width: sliders.width
                Label { text: qsTr("Opacity"); anchors.left: parent.left }
                Label { text: Math.round(opacitySlider.value); anchors.right: parent.right }
            }
            Slider { id: opacitySlider; width: sliders.width; minimumValue: 0; maximumValue: 100 }
            Item {
                height: 14
                width: sliders.width
                Label { text: qsTr("Spacing"); anchors.left: parent.left }
                Label { text: Math.round(spacingSlider.value); anchors.right: parent.right }
            }
            Slider { id: spacingSlider; width: sliders.width; minimumValue: 1; maximumValue: 200 }
            Item {
                height: 14
                width: sliders.width
                Label { text: qsTr("Hardness"); anchors.left: parent.left }
                Label { text: Math.round(hardnessSlider.value); anchors.right: parent.right }
            }
            Slider { id: hardnessSlider; width: sliders.width; minimumValue: 1; maximumValue: 100 }
            Item {
                height: 14
                width: sliders.width
                Label { text: qsTr("Roundness"); anchors.left: parent.left }
                Label { text: Math.round(roundnessSlider.value); anchors.right: parent.right }
            }
            Slider { id: roundnessSlider; width: sliders.width; minimumValue: 1; maximumValue: 10 }
            Item {
                height: 14
                width: sliders.width
                Label { text: qsTr("Angle"); anchors.left: parent.left }
                Label { text: Math.round(angleSlider.value); anchors.right: parent.right }
            }
            Slider { id: angleSlider; width: sliders.width; minimumValue: 0; maximumValue: 180 }
            Item {
                height: 14
                width: sliders.width
                Label { text: qsTr("Jitter"); anchors.left: parent.left }
                Label { text: Math.round(jitterSlider.value); anchors.right: parent.right }
            }
            Slider { id: jitterSlider; width: sliders.width; minimumValue: 0; maximumValue: 1000 }
        }

        ListView {
            model: brushSettingsModel
            anchors.fill: parent
            orientation: ListView.Vertical
            clip: true
        }
    }
}

