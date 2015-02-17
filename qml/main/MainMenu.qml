import QtQuick 2.4
import QtQuick.Controls 1.2

MenuBar {
    Menu {
        title: qsTr("File")
        MenuItem { action: actions.newAction }
        MenuItem { action: actions.openAction }
        MenuItem { action: actions.saveAction }
        MenuItem { action: actions.saveAsAction }
        MenuItem { action: actions.exportAction }
        MenuSeparator {}
        MenuItem { action: actions.quitAction }
    }

    Menu {
        title: qsTr("Edit")
        MenuItem { action: actions.undoAction }
        MenuItem { action: actions.redoAction }
        MenuItem { action: actions.clearAction }
    }

    Menu {
        title: qsTr("Layer")
        MenuItem { action: actions.newLayerAction }
        MenuItem { action: actions.deleteLayerAction }
        MenuItem { action: actions.mergeLayerAction }
        MenuItem { action: actions.duplicateLayerAction }
        MenuItem { action: actions.upLayerAction }
        MenuItem { action: actions.downLayerAction }
    }

    Menu {
        title: qsTr("View")
        MenuItem {action: actions.zoomInAction }
        MenuItem {action: actions.zoomOutAction }
        MenuItem {action: actions.rotationAction }
        MenuItem {action: actions.mirrorAction }
        MenuItem {action: actions.resetAction }
    }

    Menu {
        title: qsTr("Window")

        MenuItem {
            text: colorPicker.title
            checkable: true
            checked: colorPicker.visible
            onTriggered: colorPicker.visible = !colorPicker.visible
        }

        MenuItem {
            text: layerManager.title
            checkable: true
            checked: layerManager.visible
            onTriggered: layerManager.visible = !layerManager.visible
        }

        MenuItem {
            text: brushSettings.title
            checkable: true
            checked: brushSettings.visible
            onTriggered: brushSettings.visible = !brushSettings.visible
        }

        MenuItem {
            text: brushLibrary.title
            checkable: true
            checked: brushLibrary.visible
            onTriggered: brushLibrary.visible = !brushLibrary.visible
        }

        MenuItem {
            text: undoManager.title
            checkable: true
            checked: undoManager.visible
            onTriggered: undoManager.visible = !undoManager.visible
        }
    }

    Menu {
        title: qsTr("Help")
        MenuItem {
            text: qsTr("About...")
            onTriggered: about.open()
        }
    }
}
