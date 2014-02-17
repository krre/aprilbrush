import QtQuick 2.2
import "components"
import QtQuick.Layouts 1.1

Item {
    property real betweenSpace: (width - toolsButton.width * toolsButtonRow.children.length) / (toolsButtonRow.children.length + 1)
    width: parent.width
    height: 20

    RowLayout {
        id: toolsButtonRow
        x: betweenSpace
        anchors.verticalCenter: parent.verticalCenter
        spacing: betweenSpace

        TopButton {
            id: toolsButton
            title: qsTr("Color")
            onClicked: colorPicker.visible = !colorPicker.visible
        }

        TopButton {
            title: qsTr("Brush Settings")
            onClicked: brushSettings.visible = !brushSettings.visible
        }

        TopButton {
            title: qsTr("Brush Library")
            onClicked: brushLibrary.visible = !brushLibrary.visible
        }
    }
}
