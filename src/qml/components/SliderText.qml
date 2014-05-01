import QtQuick 2.2
import QtQuick.Controls 1.1
import QtQuick.Layouts 1.1

Column {
    property string title
    property real value: slider.value
    property real minimumValue: slider.maximumValue
    property real maximumValue: slider.maximumValue
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

