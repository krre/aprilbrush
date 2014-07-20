import QtQuick 2.3
import QtQuick.Controls.Styles 1.1
import QtQuick.Layouts 1.1
import QtQuick.Controls 1.1

TabViewStyle {
    tabsMovable: true
    tab: Rectangle {
        border.color: styleData.selected ? "black" : "gray"
        implicitWidth: styleData.selected ? Math.max(text.text.length * text.font.pixelSize / 1.5, 80) : Math.min(control.width / tabView.count, 80)
        implicitHeight: 25
        color: styleData.selected ? "white" : "lightgray"

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
                text: "x"
                implicitWidth: 15
                implicitHeight: 15
                anchors.verticalCenter: parent.verticalCenter
                anchors.right: parent.right
                anchors.rightMargin: 2
                onClicked: tabView.removeTab(styleData.index)
            }
        }
    }
}
