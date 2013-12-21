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
import QtQuick.Layouts 1.0
import QtGraphicalEffects 1.0
import "utils.js" as Utils
import "components"

ToolWindow {
    text: "Color"
    id: root

    property real h
    property real s
    property real v
    property color color: "blue"

    property int minWindowSize: Math.min(columnLayout.width, columnLayout.height)
    property real ringWidth: 0.75

    onColorChanged: setColor()

    function setColor() {
            var hsvColor = Utils.rgbToHsv(color)
            h = hsvColor.h
            s = hsvColor.s
            v = hsvColor.v
    }

    ColumnLayout {
        id: columnLayout
        anchors.fill: parent

        // Color ring
        Rectangle {
            id: outerCircle
            Layout.alignment: Qt.AlignCenter
            Layout.fillWidth: true
            Layout.fillHeight: true
            Layout.maximumWidth: minWindowSize
            Layout.maximumHeight: minWindowSize

            radius: width / 2
            anchors.centerIn: parent
            antialiasing: true

            ConicalGradient {
                anchors.fill: parent
                angle: 90
                clip: true
                source: parent
                gradient: Gradient {
                    GradientStop {position: 0 / 6; color: "red"}
                    GradientStop {position: 1 / 6; color: "magenta"}
                    GradientStop {position: 2 / 6; color: "blue"}
                    GradientStop {position: 3 / 6; color: "cyan"}
                    GradientStop {position: 4 / 6; color: "lime"}
                    GradientStop {position: 5 / 6; color: "yellow"}
                    GradientStop {position: 6 / 6; color: "red"}
                }
            }

            // Hue picker
            Rectangle {
                id: pickerHue
                property int sizePickerHue: 3

                x: parent.width / 2
                y: (parent.height - sizePickerHue) / 2
                width: parent.width / 2
                height: sizePickerHue
                color: "white"
                antialiasing: true
                transform: Rotation {
                    id: pickerHueAngle
                    origin.x: 0
                    origin.y: pickerHue.height / 2
                    angle: (1 - h) * 360
                }
            }

            MouseArea {
                anchors.fill: parent
                function handleMouseHue(mouse) {
                    if (mouse.buttons & Qt.LeftButton) {
                        var radianAngle = Math.atan2(outerCircle.height / 2 - mouse.y, mouse.x - outerCircle.width / 2)
                        var degreeAngle = (1 - radianAngle * 0.5 / Math.PI)
                        h = degreeAngle < 1 ? 1 - degreeAngle : 2 - degreeAngle
                        color = Utils.hsvToHsl(h, s, v, 1)
                    }
                }
                onPositionChanged: handleMouseHue(mouse)
                onPressed: handleMouseHue(mouse)
            }


            // Clearing inner circle
            Rectangle {
                id: innerCircle
                width: outerCircle.width * ringWidth
                height: outerCircle.height * ringWidth
                anchors.centerIn: parent
                radius: outerCircle.width * ringWidth / 2
                antialiasing: true
                color: palette.toolBgColor
            }

            // Color square
            Item {
                id: squareSV
                width: outerCircle.width * ringWidth / Math.sqrt(2)
                height: outerCircle.width * ringWidth / Math.sqrt(2)
                anchors.centerIn: parent

                Rectangle {
                    anchors.fill: parent;
                    rotation: -90
                    gradient: Gradient {
                        GradientStop {position: 0.0; color: "white"}
                        GradientStop {position: 1.0; color: Qt.hsla(h, 1, 0.5, 1)}
                    }
                }
                Rectangle {
                    anchors.fill: parent
                    gradient: Gradient {
                        GradientStop {position: 1.0; color: "#FF000000"}
                        GradientStop {position: 0.0; color: "#00000000"}
                    }
                }

                // Saturation/Value picker
                Item {
                    id: pickerSV
                    x: s * parent.width
                    y: (1 - v) * parent.height
                    property int radiusPickerSV: 5

                    Rectangle {
                        x: -parent.radiusPickerSV
                        y: -parent.radiusPickerSV
                        width: parent.radiusPickerSV * 2
                        height: parent.radiusPickerSV * 2
                        radius: parent.radiusPickerSV
                        border.color: (pickerSV.x > squareSV.width / 2) || (pickerSV.y > squareSV.height / 2) ? "white" : "black"
                        border.width: 2
                        color: "transparent"
                        antialiasing: true
                    }
                }

                MouseArea {
                    anchors.fill: parent
                    function handleMouseSV(mouse) {
                        if (mouse.buttons & Qt.LeftButton) {
                            s = Math.max(0, Math.min(width, mouse.x)) / parent.width
                            v = 1 - Math.max(0, Math.min(height, mouse.y)) / parent.height
                            color = Utils.hsvToHsl(h, s, v, 1)
                        }
                    }
                    onPositionChanged: handleMouseSV(mouse)
                    onPressed: handleMouseSV(mouse)
                }
            }
        }
    }
}

