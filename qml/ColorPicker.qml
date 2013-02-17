import QtQuick 2.0
import QtGraphicalEffects 1.0

Item {
    id: name
    width: 200
    height: 200
    property int minWindowSize: Math.min(name.width, name.height)

    ConicalGradient {
        id: conicalGradient
        width: minWindowSize
        height: minWindowSize
        anchors.centerIn: parent
        angle: 90

        gradient: Gradient {
            GradientStop {position: 0; color: "red"}
            GradientStop {position: 1; color: "blue"}
        }
    }

    MouseArea {
        anchors.fill: parent
        drag.target: parent
        //onClicked: name.z = 1
    }
}


