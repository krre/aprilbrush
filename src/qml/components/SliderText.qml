import QtQuick 2.6
import QtQuick.Controls 1.4
import QtQuick.Layouts 1.3

Column {
    property string title
    property alias value: slider.value
    property alias minimumValue: slider.minimumValue
    property alias maximumValue: slider.maximumValue
    spacing: 2

    RowLayout {
        width: parent.width
        Label {
            text: title
        }

        SpinBox {
            anchors.right: parent.right
            Layout.preferredWidth: 50
            horizontalAlignment: Qt.AlignRight
            value: slider.value
            minimumValue: slider.minimumValue
            maximumValue: slider.maximumValue
            onValueChanged: slider.value = value
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

