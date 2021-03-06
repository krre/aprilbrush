import QtQuick 2.11
import QtQuick.Layouts 1.3
import QtGraphicalEffects 1.0
import "../components"
import "../../js/utils.js" as Utils

Panel {
    id: root
    title: qsTr("Color Picker")
    property real h
    property real s
    property real v
    property color color: Settings.value(objectName, "color", "#000000")
    property bool changeColorByPicker: false
    property int minSize: Math.min(width, height) - 14 // Panel.content.anchors.margins * 2
    property real ringRatio: 0.75

    objectName: "ColorPicker"

    onColorChanged: {
        if (!changeColorByPicker) {
            var hsv = Core.colorToHsv(color)
            h = Math.max(hsv.h, 0)
            s = hsv.s
            v = hsv.v
        }
    }

    Component.onDestruction: Settings.setValue(objectName, "color", String(color))

    // Color ring
    Rectangle {
        id: ring
        anchors.centerIn: parent
        width: minSize
        height: minSize
        radius: width / 2
        antialiasing: true
        color: "transparent"

        ConicalGradient {
            anchors.fill: parent
            angle: 90
            clip: true
            source: innerCircle
            gradient: Gradient {
                GradientStop { position: 0 / 6; color: "red" }
                GradientStop { position: 1 / 6; color: "magenta" }
                GradientStop { position: 2 / 6; color: "blue" }
                GradientStop { position: 3 / 6; color: "cyan" }
                GradientStop { position: 4 / 6; color: "lime" }
                GradientStop { position: 5 / 6; color: "yellow" }
                GradientStop { position: 6 / 6; color: "red" }
            }

            // Clearing inner circle
            Rectangle {
                id: innerCircle
                anchors.fill: parent
                border.color: "green"
                border.width: parent.width * (1 - ringRatio) / 2
                radius: parent.width
                antialiasing: true
                color: "transparent"
                visible: false
            }
        }

        // Hue picker
        Rectangle {
            id: pickerHue
            property int sizePickerHue: 3
            x: parent.width * (1 + ringRatio) / 2
            y: parent.height / 2
            width: parent.width * (1 - ringRatio) / 2
            height: sizePickerHue
            color: "white"
            antialiasing: true
            transform: Rotation {
                origin.x: -ring.width * ringRatio / 2
                angle: (1 - h) * 360
            }
        }

        MouseArea {
            anchors.fill: parent

            onPositionChanged: handleMouseHue(mouse)
            onPressed: handleMouseHue(mouse)

            function handleMouseHue(mouse) {
                if (mouse.buttons & Qt.LeftButton) {
                    var radianAngle = Math.atan2(parent.height / 2 - mouse.y, mouse.x - parent.width / 2)
                    h = (radianAngle > 0 ? radianAngle : 2 * Math.PI + radianAngle) / Math.PI / 2
                    changeColorByPicker = true
                    color = Core.hsvToColor(h, s, v)
                    changeColorByPicker = false
                }
            }
        }

        // Color square
        Item {
            id: squareSV
            width: parent.width * ringRatio / Math.sqrt(2)
            height: parent.width * ringRatio / Math.sqrt(2)
            anchors.centerIn: parent

            Rectangle {
                anchors.fill: parent
                rotation: -90
                gradient: Gradient {
                    GradientStop { position: 0.0; color: "white" }
                    GradientStop { position: 1.0; color: Qt.hsla(h, 1, 0.5, 1) }
                }
            }

            Rectangle {
                anchors.fill: parent
                gradient: Gradient {
                    GradientStop { position: 1.0; color: "#FF000000" }
                    GradientStop { position: 0.0; color: "#00000000" }
                }
            }

            // Saturation/Value picker
            Item {
                id: pickerSV
                property int radiusPickerSV: 5
                x: s * parent.width
                y: (1 - v) * parent.height

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

                onPositionChanged: handleMouseSV(mouse)
                onPressed: handleMouseSV(mouse)

                function handleMouseSV(mouse) {
                    if (mouse.buttons & Qt.LeftButton) {
                        s = Math.max(0, Math.min(width, mouse.x)) / parent.width
                        v = 1 - Math.max(0, Math.min(height, mouse.y)) / parent.height
                        changeColorByPicker = true
                        color = Core.hsvToColor(h, s, v)
                        changeColorByPicker = false
                    }
                }
            }
        }
    }
}

