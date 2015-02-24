import QtQuick 2.4
import QtQuick.Controls 1.3
import "../utils.js" as Utils
import "../undo.js" as Undo
import "../enums.js" as Enums

Item {
    property alias newAction: newAction
    property alias openAction: openAction
    property alias saveAction: saveAction
    property alias saveAsAction: saveAsAction
    property alias exportAction: exportAction
    property alias quitAction: quitAction

    property alias undoAction: undoAction
    property alias redoAction: redoAction
    property alias clearAction: clearAction

    property alias newLayerAction: newLayerAction
    property alias deleteLayerAction: deleteLayerAction
    property alias mergeLayerAction: mergeLayerAction
    property alias duplicateLayerAction: duplicateLayerAction
    property alias upLayerAction: upLayerAction
    property alias downLayerAction: downLayerAction

    property alias zoomInAction: zoomInAction
    property alias zoomOutAction: zoomOutAction
    property alias rotationAction: rotationAction
    property alias mirrorAction: mirrorAction
    property alias resetAction: resetAction

    Action {
        id: newAction
        text: qsTr("New")
        shortcut: "Ctrl+N"
        onTriggered: newImage()
    }

    Action {
        id: openAction
        text: qsTr("Open...")
        shortcut: "Ctrl+O"
        onTriggered: {
            fileDialog.mode = Enums.FileOpen
            fileDialog.open()
        }
    }

    Action {
        id: saveAction
        text: qsTr("Save")
        shortcut: "Ctrl+S"
        onTriggered: {
            if (oraPath === "") {
                fileDialog.mode = Enums.FileSave
                fileDialog.open()
            } else {
                Utils.saveOra()
            }
        }
        enabled: isDirty
    }

    Action {
        id: saveAsAction
        text: qsTr("Save As...")
        shortcut: "Ctrl+Shift+S"
        onTriggered: {
            fileDialog.mode = Enums.FileSave
            fileDialog.open()
        }
    }

    Action {
        id: exportAction
        text: qsTr("Export...")
        shortcut: "Ctrl+E"
        onTriggered: {
            fileDialog.mode = Enums.FileExport
            fileDialog.open()
        }
        enabled: layerModel && layerModel.count > 0
    }

    Action {
        id: quitAction
        text: qsTr("Quit")
        shortcut: "Ctrl+Q"
        onTriggered: mainRoot.close()
    }

    Action {
        id: undoAction
        text: qsTr("Undo")
        shortcut: "Ctrl+Z"
        onTriggered: {
            undoManager.undoView.decrementCurrentIndex()
            undoManager.run(undoManager.undoView.currentIndex)
        }
        enabled: undoManager.undoView.currentIndex > 0
    }

    Action {
        id: redoAction
        text: qsTr("Redo")
        shortcut: "Ctrl+Shift+Z"
        onTriggered: {
            undoManager.undoView.incrementCurrentIndex()
            undoManager.run(undoManager.undoView.currentIndex)
        }
        enabled: undoModel ? undoManager.undoView.currentIndex < undoModel.count - 1 : false
    }

    Action {
        id: clearAction
        text: qsTr("Clear")
        shortcut: "Delete"
        onTriggered: undoManager.add(Undo.clearLayer())
        enabled: currentLayerIndex >= 0
    }

    // layer management

    Action {
        id: newLayerAction
        text: qsTr("New")
        shortcut: "Shift+Ctrl+N"
        onTriggered: layerManager.addLayer()
    }

    Action {
        id: deleteLayerAction
        text: qsTr("Delete")
        onTriggered: undoManager.add(Undo.deleteLayer())
        enabled: layerManager.layerView.count > 0
    }

    Action {
        id: mergeLayerAction
        text: qsTr("Merge Down")
        enabled: currentLayerIndex < layerManager.layerView.count - 2
        onTriggered: undoManager.add(Undo.mergeLayer())
    }

    Action {
        id: duplicateLayerAction
        text: qsTr("Duplicate")
        onTriggered: undoManager.add(Undo.duplicateLayer())
        enabled: layerManager.layerView.count > 1
    }

    Action {
        id: upLayerAction
        text: qsTr("Up")
        enabled: currentLayerIndex > 0
        onTriggered: undoManager.add(Undo.raiseLayer())
    }

    Action {
        id: downLayerAction
        text: qsTr("Down")
        enabled: currentLayerIndex < layerManager.layerView.count - 2
        onTriggered: undoManager.add(Undo.lowerLayer())
    }

    // canvas transform

    Action {
        id: zoomInAction
        text: qsTr("Zoom In")
        shortcut: "."
        onTriggered: canvasArea.zoomIn()
    }

    Action {
        id: zoomOutAction
        text: qsTr("Zoom Out")
        shortcut: ","
        onTriggered: canvasArea.zoomOut()
    }

    Action {
        id: rotationAction
        text: qsTr("Rotation")
        shortcut: "R"
        onTriggered: canvasArea.rotation += 90
    }

    Action {
        id: mirrorAction
        text: qsTr("Mirror")
        shortcut: "M"
        onTriggered: canvasArea.mirror *= -1
    }

    Action {
        id: resetAction
        text: qsTr("Reset")
        shortcut: "F12"
        onTriggered: canvasArea.resetTransform()
    }
}

