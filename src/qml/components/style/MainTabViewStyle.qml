import QtQuick 2.6
import QtQuick.Controls 1.5
import QtQuick.Layouts 1.3
import QtQuick.Controls.Styles 1.4
import "../../../3rdparty/font-awesome/fontawesome.js" as FontAwesome

TabViewStyle {
    tabsMovable: true
    tabOverlap: -5
    tab: Rectangle {
        implicitWidth: styleData.selected ? Math.max(text.text.length * text.font.pixelSize / 1.5, 80) : Math.min(control.width / tabView.count, 80)
        implicitHeight: 25
        color: "#e6e6e6"
        border.width: 1
        border.color: styleData.selected ? "#7d91f5" : "transparent"

        RowLayout {
            anchors.fill: parent
            spacing: 0

            Text {
                id: text
                Layout.fillWidth: true
                anchors.verticalCenter: parent.verticalCenter
                horizontalAlignment: Text.AlignHCenter
                text: styleData.title
                elide: Text.ElideLeft
            }

            ToolButton {
                id: closeButton
                implicitWidth: 15
                implicitHeight: 15
                anchors.verticalCenter: parent.verticalCenter
                anchors.right: parent.right
                anchors.rightMargin: 2
                style: ButtonStyle {
                    background: Rectangle {
                        color: control.pressed ? "#b42328" : (control.hovered ? "#dc3235" : "transparent")
                        radius: control.implicitWidth
                        antialiasing: true
                    }

                    label: Text {
                        verticalAlignment: Text.AlignVCenter
                        horizontalAlignment: Text.AlignHCenter
                        font.family: "FontAwesome"
                        text: FontAwesome.Icon.Remove
                        font.pointSize: 8
                        color: control.pressed || control.hovered ? "white" : "gray"
                    }
                }

                onClicked: control.removeTab(styleData.index)
            }
        }
    }

    tabBar: Rectangle {
        color: sysPalette.window
    }
}
