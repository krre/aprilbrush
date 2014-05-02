import QtQuick 2.2
import QtQuick.Controls 1.1

Item {
    property alias newImageAction: newImageAction
    property alias openAction: openAction
    property alias saveAction: saveAction
    property alias saveAsAction: saveAsAction
    property alias closeAction: closeAction
    property alias closeAllAction: closeAllAction
    property alias closeOthersAction: closeOthersAction
    property alias quitAction: quitAction

    property alias clearAction: clearAction

    property alias newLayerAction: newLayerAction
    property alias deleteLayerAction: deleteLayerAction
    property alias mergeLayerAction: mergeLayerAction
    property alias duplicateLayerAction: duplicateLayerAction
    property alias upLayerAction: upLayerAction
    property alias downLayerAction: downLayerAction

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
        }
        tooltip: qsTr("New an Image")
    }

    Action {
        id: openAction
        text: qsTr("Open")
        shortcut: StandardKey.Open
        onTriggered: fileDialog.open()
        tooltip: qsTr("Open an Image")
    }

    Action {
        id: saveAction
        text: qsTr("Save")
        shortcut: StandardKey.Save
        onTriggered: print("save")
        tooltip: qsTr("Save an Image")
    }

    Action {
        id: saveAsAction
        text: qsTr("Save As...")
        shortcut: StandardKey.SaveAs
        onTriggered: print("save as")
        tooltip: qsTr("Save as an Image")
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
        enabled: layerManager.layerView.count > 0
    }

    Action {
        id: mergeLayerAction
        text: qsTr("Merge Down")
        enabled: currentLayerIndex < layerManager.layerView.count - 1
    }

    Action {
        id: duplicateLayerAction
        text: qsTr("Duplicate")
        enabled: layerManager.layerView.count > 0
    }

    Action {
        id: upLayerAction
        text: qsTr("Up")
        enabled: layerManager.layerView.currentIndex > 0
        onTriggered: layerModel.move(currentLayerIndex, currentLayerIndex - 1, 1)
    }

    Action {
        id: downLayerAction
        text: qsTr("Down")
        enabled: currentLayerIndex < layerManager.layerView.count - 1
        onTriggered: layerModel.move(currentLayerIndex, currentLayerIndex + 1, 1)
    }
}

