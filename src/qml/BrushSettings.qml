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
import QtQuick.Controls 1.1
import QtQuick.Layouts 1.0
import "components"

ToolWindow {
    id: root
    text: "Brush Settings"

    property alias size: sizeSlider
    property alias opaque: opacitySlider
    property alias spacing: spacingSlider
    property alias hardness: hardnessSlider
    property alias roundness: roundnessSlider
    property alias angle: angleSlider
    property alias jitter: jitterSlider

    ScrollView {
        id: scrollView
        anchors.fill: parent

        ColumnLayout {
            width: parent.width
            height: childrenRect.height

            SliderText {
                id: sizeSlider
                Layout.preferredWidth: scrollView.viewport.width
                text: qsTr("Size")
                minValue: 1
                maxValue: 200
            }

            SliderText {
                id: opacitySlider
                Layout.preferredWidth: scrollView.viewport.width
                text: qsTr("Opacity")
                minValue: 0
                maxValue: 100
            }

            SliderText {
                id: spacingSlider
                Layout.preferredWidth: scrollView.viewport.width
                text: qsTr("Spacing")
                minValue: 1
                maxValue: 100
            }

            SliderText {
                id: hardnessSlider
                Layout.preferredWidth: scrollView.viewport.width
                text: qsTr("Hardness")
                minValue: 1
                maxValue: 100
            }

            SliderText {
                id: roundnessSlider
                Layout.preferredWidth: scrollView.viewport.width
                text: qsTr("Roundness")
                minValue: 1
                maxValue: 100
            }

            SliderText {
                id: angleSlider
                Layout.preferredWidth: scrollView.viewport.width
                text: qsTr("Angle")
                minValue: 0
                maxValue: 180
            }

            SliderText {
                id: jitterSlider
                Layout.preferredWidth: scrollView.viewport.width
                text: qsTr("Jitter")
                minValue: 0
                maxValue: 1000
            }
        }
    }
}

