import QtQuick 2.0
import "components"

Item {
    id: name
    width: 500
    height: 62

    Rectangle {
        id: rect
        anchors.fill: parent
        radius: 10
        antialiasing: true
        border.color: "gray"
        color: "#f5f5f5"

        MouseArea {
            anchors.fill: parent
            hoverEnabled: true
        }

        Row {
            height: parent.height
            width: childrenRect.width
            anchors.centerIn: parent
            spacing: 5

            DockItem {
                name: brushSettings.title
                onClicked: brushSettings.visible = true
            }

            DockItem {
                name: "Layers" // TODO: bind on layerManager object
                onClicked: layerManagerVisible = true
            }

            DockItem {
                name: colorPicker.title
                onClicked: colorPicker.visible = true
            }

            DockItem {
                name: "Undo History" // TODO: bind on undoManager object
                onClicked: undoManagerVisible = true;

            }

            DockItem {
                name: brushLibrary.title
                onClicked: brushLibrary.visible = true
            }
        }
    }

    Shadow {
        surface: rect

    }
}
