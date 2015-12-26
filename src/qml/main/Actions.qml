import QtQuick 2.6
import QtQuick.Controls 1.5
import "../../js/utils.js" as Utils
import "../../js/undo.js" as Undo
import "../../js/enums.js" as Enums

Item {

    property alias newLayerAction: newLayerAction
    property alias deleteLayerAction: deleteLayerAction
    property alias mergeLayerAction: mergeLayerAction
    property alias duplicateLayerAction: duplicateLayerAction
    property alias upLayerAction: upLayerAction
    property alias downLayerAction: downLayerAction

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
        enabled: layerManager.layerView.count > 0
        onTriggered: undoManager.add(Undo.deleteLayer())
    }

    Action {
        id: mergeLayerAction
        text: qsTr("Merge Down")
        enabled: layerManager.currentIndex <= layerManager.layerView.count - 2
        onTriggered: undoManager.add(Undo.mergeLayer())
    }

    Action {
        id: duplicateLayerAction
        text: qsTr("Duplicate")
        enabled: layerManager.layerView.count > 0
        onTriggered: undoManager.add(Undo.duplicateLayer())
    }

    Action {
        id: upLayerAction
        text: qsTr("Up")
        enabled: layerManager.currentIndex > 0
        onTriggered: undoManager.add(Undo.raiseLayer())
    }

    Action {
        id: downLayerAction
        text: qsTr("Down")
        enabled: layerManager.currentIndex <= layerManager.layerView.count - 2
        onTriggered: undoManager.add(Undo.lowerLayer())
    }
}

