import QtQuick 2.0
import QtGraphicalEffects 1.0
import "utils.js" as Utils
import "components"

Window {
    title: "Color"
    id: root

    property real hueColor: 0
    property real saturationColor: 0
    property real valueColor: 0
    property color pickColor: Qt.hsla(0, 0, 0, 0)
    property int minWindowSize: Math.min(container.width, container.height)
    property real ringWidth: 0.75

    signal colorChanged

    Item {
        id: container

        anchors.fill: parent
        Component.onCompleted: console.log(minWindowSize)

        // Color ring
        Rectangle {
            id: outerCircle
            width: minWindowSize
            height: minWindowSize
            radius: outerCircle.width / 2
            anchors.centerIn: parent
            antialiasing: true

            ConicalGradient {
                anchors.fill: parent
                angle: 90
                clip: true
                source: outerCircle
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
                    angle: 0
                }
            }

            MouseArea {
                anchors.fill: parent
                function handleMouseHue(mouse) {
                    if (mouse.buttons & Qt.LeftButton) {
                        var radianAngle = Math.atan2(outerCircle.height / 2 - mouse.y, mouse.x - outerCircle.width / 2)
                        var degreeAngle = 360 - radianAngle * 180 / Math.PI
                        pickerHueAngle.angle = degreeAngle
                        hueColor = (degreeAngle < 360 ? 360 - degreeAngle : 720 - degreeAngle) / 360
                        pickColor = Utils.hslColor(hueColor, saturationColor, valueColor, 1)
                        colorChanged()
                    }
                }
                onPositionChanged: handleMouseHue(mouse)
                onPressed: handleMouseHue(mouse)
            }
        }

        // Clearing inner circle
        Rectangle {
            id: innerCircle
            width: outerCircle.width * ringWidth
            height: outerCircle.height * ringWidth
            anchors.centerIn: parent
            radius: outerCircle.width * ringWidth / 2
            antialiasing: true
            color: "#eeeeee"
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
                    GradientStop {position: 1.0; color: Qt.hsla(hueColor, 1, 0.5, 1)}
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
                        pickerSV.x = Math.max(0, Math.min(width, mouse.x))
                        pickerSV.y = Math.max(0, Math.min(height, mouse.y))
                        var saturation = pickerSV.x / parent.width
                        saturationColor = saturation
                        var value = 1 - pickerSV.y / parent.height
                        valueColor = value
                        pickColor = Utils.hslColor(hueColor, saturationColor, valueColor, 1)
                        colorChanged()
                    }
                }
                onPositionChanged: handleMouseSV(mouse)
                onPressed: handleMouseSV(mouse)
            }
        }
    }
}

