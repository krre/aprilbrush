import QtQuick 2.0
import QtQuick.Window 2.0
import BrushEngine 1.0
import "components"
import "utils.js" as Utils

Item {
    width: 1000
    height: 600
    focus: true

    Keys.onPressed: {
        if (event.key == Qt.Key_Delete) brush.clear()
        if (event.key == Qt.Key_S) brushSettings.visible ? brushSettings.visible = false : brushSettings.visible = true
        if (event.key == Qt.Key_C) colorPicker.visible ? colorPicker.visible = false : colorPicker.visible = true
        if (event.key == Qt.Key_L) layerManager.visible ? layerManager.visible = false : layerManager.visible = true
        if (event.key == Qt.Key_P) brushLibrary.visible ? brushLibrary.visible = false : brushLibrary.visible = true

    }

    CheckerBoard {
        cellSide: 30
        width: Screen.width
        height: Screen.height
    }

    Brush {
        id: brush
        color: "red"
        size: brushSettings.size
        spacing: brushSettings.spacing
        hardness: brushSettings.hardness
        opacity: brushSettings.opacity_
        roundness: brushSettings.roundness
        angle: brushSettings.angle
    }

    MouseArea {
        anchors.fill: parent
        onPressed: if (layersModel.count > 0) brush.paintDab(mouseX, mouseY)
        onReleased: brush.setTouch(false)
        onPositionChanged: if (layersModel.count > 0) brush.paintDab(mouseX, mouseY)
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
        id: layersModel
        ListElement {name: "Layer-01"; number: 1; colorImage: "transparent"; enable: true }
        ListElement {name: "Background"; number: 0; colorImage: "white"; enable: true }
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



