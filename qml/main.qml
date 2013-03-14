import QtQuick 2.0
import QtQuick.Window 2.0
import BrushEngine 1.0
import "components"
import "utils.js" as Utils

Item {
    property alias currentPage: pageManager.currentPage
    property alias currentLayer: layerManager.currentLayer
    property variant layersModel: currentPage > -1 ? pagesModel.get(currentPage).layerSet : 0

    width: 1000
    height: 600
    focus: true

    Keys.onPressed: {
        if (event.key == Qt.Key_Delete) {
            var hashPageLayer = pagesModel.get(currentPage).hashPage * 1000 + layersModel.get(currentLayer).hashLayer
            brush.setLayer(hashPageLayer)
            brush.clear()
        }
        if (event.key == Qt.Key_S) brushSettings.visible = !brushSettings.visible
        if (event.key == Qt.Key_C) colorPicker.visible = !colorPicker.visible
        if (event.key == Qt.Key_L) layerManager.visible = !layerManager.visible
        if (event.key == Qt.Key_P) brushLibrary.visible = !brushLibrary.visible
    }

    CheckerBoard {
        cellSide: 30
        width: Screen.width
        height: Screen.height
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
    }

    MouseArea {
        anchors.fill: parent
        onPressed: {
            if (pagesModel.count > 0 && layersModel.count > 0) {
                var hashPageLayer = pagesModel.get(currentPage).hashPage * 1000 + layersModel.get(currentLayer).hashLayer
                brush.setLayer(hashPageLayer)
                brush.paintDab(mouseX, mouseY)
                //console.log(hashPageLayer)
            }
        }
        onReleased: brush.setTouch(false)
        onPositionChanged: {
            if (pagesModel.count > 0 && layersModel.count > 0)
                brush.paintDab(mouseX, mouseY)
        }
    }

    CanvasArea {
        id: canvasArea
        width: Screen.width
        height: Screen.height
    }

    PageManager {
        id: pageManager
        width: 600
        height: 34
        anchors.horizontalCenter: parent.horizontalCenter
    }

    ListModel {
        id: pagesModel
        ListElement { name: "Page-001"; hashPage: 001; activeLayer: 0; layerSet: [
                ListElement {name: "Layer-002"; hashLayer: 002; colorImage: "transparent"; enable: true },
                ListElement {name: "Layer-001"; hashLayer: 001; colorImage: "white"; enable: true }
            ]
        }
    }

    LayerManager {
        id: layerManager
        x: 20
        y: 300
        //visible: false
    }

    BrushSettings {
        id: brushSettings
        x: 780
        y: 20
        height: 250
        //visible: false
    }

    ColorPicker {
        id: colorPicker
        x: 20
        y: 50
        //visible: false
        onColorChanged: brush.color = colorPicker.pickColor
    }

    BrushLibrary {
        id: brushLibrary
        x: 780
        y: 320
        visible: false
    }
}



