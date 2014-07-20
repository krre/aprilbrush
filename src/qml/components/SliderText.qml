import QtQuick 2.3
import QtQuick.Controls 1.1
import QtQuick.Layouts 1.1

Column {
    property string title
    property alias value: slider.value
    property alias minimumValue: slider.minimumValue
    property alias maximumValue: slider.maximumValue
    spacing: 5

    RowLayout {
        width: parent.width
        Text {
            text: title
        }

        Text {
            anchors.right: parent.right
            text: slider.value
        }
    }

    Slider {
        id: slider
        width: parent.width
        minimumValue: 0
        maximumValue: 100
        stepSize: 1
    }
}

