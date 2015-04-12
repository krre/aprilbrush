import QtQuick 2.4
import QtQuick.Controls 1.3
import "../utils.js" as Utils
import "../undo.js" as Undo
import "../enums.js" as Enums

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
}

