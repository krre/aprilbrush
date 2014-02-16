import QtQuick 2.2
import QtQuick.Controls 1.1
import QtQuick.Controls.Styles 1.1

Slider {
    property string title
    minimumValue: 0
    maximumValue: 100
    stepSize: 1

    style: SliderStyle {
        groove: Rectangle {
            id: grooveRect
            implicitWidth: root.width
            implicitHeight: sliderTitle.height * 1.5
            color: "transparent"
            antialiasing: true
            border.color: "gray"
            radius: height / 2

            Item {
                clip: true
                width: styleData.handlePosition
                height: parent.height
                Rectangle {
                    width: grooveRect.width
                    height: parent.height
                    radius: height / 2
                    antialiasing: true
                    color: "gray"
                }
            }

            Text {
                id: sliderTitle
                text: control.title
                anchors.left: parent.left
                anchors.leftMargin: parent.height / 2
                anchors.verticalCenter: parent.verticalCenter
                color: "white"
            }
            Text {
                text: control.value
                anchors.verticalCenter: parent.verticalCenter
                anchors.right: parent.right
                anchors.rightMargin: parent.height / 2
                color: "white"
            }
        }
        handle: Item {}
    }
}

