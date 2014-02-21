import QtQuick 2.2
import QtQuick.Controls 1.1
import "components"
import "style"

Rectangle {
    height: 28
    color: "black"
    opacity: 0.8

    Row {
        x: 10
        width: parent.width
        anchors.verticalCenter: parent.verticalCenter
        spacing: 10

        Button {
            id: toolsButton
            text: qsTr("Color")
            style: ButtonStyle {}
            onClicked: colorPicker.visible = !colorPicker.visible
        }

        Button {
            text: qsTr("Brush Settings")
            style: ButtonStyle {}
            onClicked: brushSettings.visible = !brushSettings.visible
        }

        Button {
            text: qsTr("Layers")
            style: ButtonStyle {}
            onClicked: layerManager.visible = !layerManager.visible
        }

        Button {
            text: qsTr("Brush Library")
            style: ButtonStyle {}
            onClicked: brushLibrary.visible = !brushLibrary.visible
        }

        Button {
            text: qsTr("Clear")
            style: ButtonStyle {}
            onClicked: canvasView.currentItem.clear()
        }
    }

    Button {
        anchors.verticalCenter: parent.verticalCenter
        anchors.right: parent.right
        anchors.rightMargin: 10
        text: pageManager.collapse ? qsTr("Show Tabs") : qsTr("Hide Tabs")
        style: ButtonStyle {}
        onClicked: pageManager.collapse = !pageManager.collapse
    }
}
