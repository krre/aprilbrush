import QtQuick 2.10
import QtQuick.Controls 1.6
import QtQuick.Layouts 1.3
import QtQuick.Controls.Styles 1.4
import "../../../3rdparty/font-awesome/fontawesome.js" as FontAwesome

TabViewStyle {
    tabsMovable: true
    tabOverlap: -5
    tab: Rectangle {
        implicitWidth: Math.max(fontMetrics.advanceWidth(title.text), 80) + closeButton.implicitWidth
        implicitHeight: 25
        color: "#e6e6e6"
        border.width: 1
        border.color: styleData.selected ? "#7d91f5" : "transparent"

        FontMetrics {
            id: fontMetrics
            font.family: title.font.family
        }

        RowLayout {
            anchors.fill: parent
            spacing: 0

            Label {
                id: title
                Layout.fillWidth: true
                Layout.alignment: Qt.AlignVCenter
                horizontalAlignment: Text.AlignHCenter
                text: styleData.title
                elide: Text.ElideRight
            }

            ToolButton {
                id: closeButton
                implicitWidth: 15
                implicitHeight: 15
                Layout.alignment: Qt.AlignVCenter | Qt.AlignRight
                Layout.rightMargin: 2

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
