import QtQuick 2.0
import QtQuick.Controls 1.1

Item {
    property alias minValue: slider.minimumValue
    property alias maxValue: slider.maximumValue
    property alias value: slider.value
    property alias text: name.text
    height: childrenRect.height

    Label {
        id: name
        text: "Slider"
        color: "white"
        anchors.left: parent.left
    }

    Label {
        text: Math.round(slider.value)
        color: "white"
        anchors.right: parent.right
        anchors.rightMargin: 5
    }

    Slider {
        id: slider
        width: parent.width - 5
        anchors.top: name.bottom
        anchors.topMargin: 2
    }
}
