import QtQuick 2.3
import QtQuick.Controls 1.2
import "../utils.js" as Utils
import "../undo.js" as Undo

Item {
    property alias newImageAction: newImageAction
    property alias openAction: openAction
    property alias saveAction: saveAction
    property alias saveAsAction: saveAsAction
    property alias exportAction: exportAction
    property alias closeAction: closeAction
    property alias closeAllAction: closeAllAction
    property alias closeOthersAction: closeOthersAction
    property alias quitAction: quitAction

    property alias brushAction: brushAction
    property alias eraserAction: eraserAction
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

    // image management

    Action {
        id: newImageAction
        text: qsTr("New")
        shortcut: StandardKey.New
        onTriggered: {
            tabView.addTab(qsTr("Untitled ") + (tabView.count + 1), canvasArea)
            tabView.currentIndex = tabView.count - 1
            layerManager.addLayer(qsTr("Background"), "white")
            layerManager.addLayer(qsTr("Layer"), "transparent")
            layerManager.layerView.prevCurrentRow = layerManager.layerView.currentRow
            undoManager.clear()
        }
        tooltip: qsTr("New an Image")
    }

    Action {
        id: openAction
        text: qsTr("Open...")
        shortcut: StandardKey.Open
        tooltip: qsTr("Open an Image")
        onTriggered: {
            fileDialog.mode = 0
            fileDialog.open()
        }
    }

    Action {
        id: saveAction
        text: qsTr("Save")
        shortcut: StandardKey.Save
        tooltip: qsTr("Save an Image")
        onTriggered: {
            if (currentTab.oraPath === "") {
                fileDialog.mode = 1; // Save mode
                fileDialog.open()
            } else {
                Utils.saveOra()
            }
        }
        enabled: tabView.count > 0
    }

    Action {
        id: saveAsAction
        text: qsTr("Save As...")
        shortcut: StandardKey.SaveAs
        tooltip: qsTr("Save as an Image")
        onTriggered: {
            fileDialog.mode = 1
            fileDialog.open()
        }
        enabled: tabView.count > 0
    }

    Action {
        id: exportAction
        text: qsTr("Export...")
        shortcut: "Ctrl+E"
        tooltip: qsTr("Export an Image to PNG")
        onTriggered: {
            fileDialog.mode = 2
            fileDialog.open()
        }
        enabled: tabView.count > 0 && layerModel && layerModel.count > 0
    }

    Action {
        id: closeAction
        text: qsTr("Close")
        shortcut: StandardKey.Close
        onTriggered: tabView.removeTab(tabView.currentIndex)
        tooltip: qsTr("Close as an Image")
        enabled: tabView.count > 0
    }

    Action {
        id: closeAllAction
        text: qsTr("Close All")
        onTriggered: {
            while (tabView.count) {
                tabView.removeTab(0)
            }
        }
        tooltip: qsTr("Close all Images")
        enabled: tabView.count > 0
    }

    Action {
        id: closeOthersAction
        text: qsTr("Close Others")
        onTriggered: {
            var currentTab = tabView.getTab(tabView.currentIndex)
            var i = 0
            while (tabView.count > 1) {
                var tab = tabView.getTab(i)
                if (tab !== currentTab) {
                    tabView.removeTab(i)
                } else {
                    i++
                }
            }
        }
        tooltip: qsTr("Close others Images")
        enabled: tabView.count > 1
    }

    Action {
        id: quitAction
        text: qsTr("Quit")
        shortcut: StandardKey.Quit
        onTriggered: Qt.quit()
        tooltip: text
    }

    // edit management
    ExclusiveGroup {
        Action {
            id: brushAction
            text: qsTr("Brush")
            shortcut: "B"
            checkable: true
            checked: true
            onTriggered: isEraser = false
        }

        Action {
            id: eraserAction
            text: qsTr("Eraser")
            shortcut: "E"
            checkable: true
            onTriggered: isEraser = true
        }
    }

    Action {
        id: undoAction
        text: qsTr("Undo")
        shortcut: StandardKey.Undo
        onTriggered: undoManager.undoView.decrementCurrentRow()
        enabled: undoModel.count > 1
    }

    Action {
        id: redoAction
        text: qsTr("Redo")
        shortcut: StandardKey.Redo
        onTriggered: undoManager.undoView.incrementCurrentRow()
        enabled: undoManager.undoView.currentRow < undoModel.count
    }

    Action {
        id: clearAction
        text: qsTr("Clear")
        shortcut: "Delete"
        onTriggered: currentTab.canvas.clear()
        enabled: currentLayerIndex >= 0
    }

    // layer management

    Action {
        id: newLayerAction
        text: qsTr("New")
        shortcut: "Shift+Ctrl+N"
        onTriggered: layerManager.addLayer("Layer", "transparent")
        tooltip: qsTr("New Layer")
        enabled: tabView.count > 0
    }

    Action {
        id: deleteLayerAction
        text: qsTr("Delete")
        onTriggered: layerManager.deleteLayer()
        tooltip: qsTr("Delete Layer")
        enabled: layerManager.layerView.rowCount > 0
    }

    Action {
        id: mergeLayerAction
        text: qsTr("Merge Down")
        enabled: currentLayerIndex < layerManager.layerView.rowCount - 1
        onTriggered: layerManager.mergeLayer()
    }

    Action {
        id: duplicateLayerAction
        text: qsTr("Duplicate")
        enabled: layerManager.layerView.rowCount > 0
    }

    Action {
        id: upLayerAction
        text: qsTr("Up")
        enabled: layerManager.layerView.currentRow > 0
        onTriggered: layerManager.moveUpLayer()
    }

    Action {
        id: downLayerAction
        text: qsTr("Down")
        enabled: currentLayerIndex < layerManager.layerView.rowCount - 1
        onTriggered: layerManager.moveDownLayer()
    }

    // canvas transform

    Action {
        id: zoomInAction
        text: qsTr("Zoom In")
        shortcut: StandardKey.ZoomIn
        enabled: tabView.count > 0
        onTriggered: currentTab.zoom *= 1.5
    }

    Action {
        id: zoomOutAction
        text: qsTr("Zoom Out")
        shortcut: StandardKey.ZoomOut
        enabled: tabView.count > 0
        onTriggered: currentTab.zoom /= 1.5
    }

    Action {
        id: rotationAction
        text: qsTr("Rotation")
        shortcut: "R"
        enabled: tabView.count > 0
        onTriggered: currentTab.rotation += 90
    }

    Action {
        id: mirrorAction
        text: qsTr("Mirror")
        shortcut: "M"
        enabled: tabView.count > 0
        onTriggered: currentTab.mirror *= -1
    }

    Action {
        id: resetAction
        text: qsTr("Reset")
        shortcut: "0"
        enabled: tabView.count > 0
        onTriggered: currentTab.resetTransform()
    }
}

