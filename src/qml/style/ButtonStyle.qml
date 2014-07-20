import QtQuick 2.3
import QtQuick.Controls.Styles 1.1

ButtonStyle {
    background: Rectangle {
        implicitWidth: 100
        implicitHeight: 25
        antialiasing: true
        color: control.pressed ? "#222222" : control.hovered ? "#474747" : "transparent"
        border.width: control.activeFocus ? 2 : 1
        border.color: "gray"
        radius: 5
    }
    label: Text {
        text: control.text
        color: "white"
        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter
        font.pointSize: 9
        clip: true
    }
}
