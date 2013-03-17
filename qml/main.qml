import QtQuick 2.0
import QtQuick.Window 2.0
import BrushEngine 1.0
import "components"
import "utils.js" as Utils

Rectangle {
    id: main
    property real zoom: 1
    property size imageSize: Qt.size(Screen.width, Screen.height)
    //property var currentPaintSpace: pageManager.pagesView.currentItem.canvasArea.pathView.currentItem

    width: 1000
    height: 600
    focus: true
    color: "lightgray"

    Keys.onPressed: {
        //if (currentPaintSpace !== null) {
        if (pageManager.pagesView.currentItem.canvasArea.pathView.currentItem !== null) {
            if (event.key == Qt.Key_Delete) { brush.setSource(pageManager.pagesView.currentItem.canvasArea.pathView.currentItem); brush.clear() }
        }
        if (event.key == Qt.Key_S) brushSettings.visible = !brushSettings.visible
        if (event.key == Qt.Key_C) colorPicker.visible = !colorPicker.visible
        if (event.key == Qt.Key_L) layerManager.visible = !layerManager.visible
        if (event.key == Qt.Key_P) brushLibrary.visible = !brushLibrary.visible
        if (event.key == Qt.Key_Plus) zoom *= 1.5
        if (event.key == Qt.Key_Minus) zoom /= 1.5
        if (event.key == Qt.Key_0) zoom = 1
    }

    CheckerBoard {
        id: checkerBoard
        cellSide: 30
        width: imageSize.width
        height: imageSize.height
        z: 1
        scale: zoom
        anchors.centerIn: parent
    }

    Brush {
        id: brush
        color: "black"
        size: brushSettings.size
        spacing: brushSettings.spacing
        hardness: brushSettings.hardness
        opacity: brushSettings.opacity_
        roundness: brushSettings.roundness
        angle: brushSettings.angle
        //source: currentPaintSpace
        source: pageManager.pagesView.currentItem.canvasArea.pathView.currentItem
    }

    PageManager {
        id: pageManager
        width: 600
        height: 34
        anchors.horizontalCenter: parent.horizontalCenter
        z: 3
    }

    ListModel {
        id: pagesModel
        ListElement { name: "Page-001";
            layerSet: [
                ListElement {name: "Layer-002"; colorImage: "transparent"; enable: true },
                ListElement {name: "Layer-001"; colorImage: "white"; enable: true } ]
            undoSet: [ ListElement {name: "Start"}, ListElement {name: "Paint"} ]
        }
    }

    BrushSettings {
        id: brushSettings
        x: 780
        y: 20
        height: 250
        //visible: false
        z: 5
    }

    ColorPicker {
        id: colorPicker
        x: 20
        y: 50
        //visible: false
        onColorChanged: brush.color = colorPicker.pickColor
        z: 6
    }

    BrushLibrary {
        id: brushLibrary
        x: 780
        y: 320
        visible: false
        z: 7
    }
/*
    UndoManager {
        id: undoManager
        x: 750
        y: 200
        z: 8
    }
    */
}



