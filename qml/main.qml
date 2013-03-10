import QtQuick 2.0
import QtQuick.Window 2.0
import BrushEngine 1.0
import "components"
import "utils.js" as Utils

Item {
    id: container
    width: 1000
    height: 600

    CheckerBoard {
        cellSide: 30
        width: Screen.width
        height: Screen.height
    }

    CanvasArea {
        width: Screen.width
        height: Screen.height
        layersModel: layersData
        //initColor: "yellow"
    }


    Keys.onPressed: {
        if (event.key == Qt.Key_Delete) {brush.clear(); space.update()};
        if (event.key == Qt.Key_P) brushSettings.visible = true;
        if (event.key == Qt.Key_C) colorPicker.visible = true;
    }
    focus: true

    MouseArea {
        anchors.fill: parent
        onPressed: brush.paintDab(mouseX, mouseY)
        onReleased: brush.setTouch(false)
        onPositionChanged: brush.paintDab(mouseX, mouseY)
    }

    Brush {
        id: brush
        onPaintDone: space.update()
        color: "red"
        size: brushSettings.size
        spacing: brushSettings.spacing
        hardness: brushSettings.hardness
        opacity: brushSettings.opacity_
        roundness: brushSettings.roundness
        angle: brushSettings.angle
    }

/*
    // Files panel
    FilePanel {
        id: filePanel
        x: 0; y: 0
        onPressFileItem: {
            if (itemName == "New") {
                var numNextPage = Utils.zeroFill(pagePanel.pageModel.count + 1, 2)
                pagePanel.pageModel.append({"name": "Untitled " + numNextPage})
            }
        }
    }

    // Pages panel
    PagePanel
    {
        id: pagePanel
        anchors.horizontalCenter: parent.horizontalCenter
        width: parent.width - filePanel.width * 2
    }
*/
    ListModel {
        id: layersData
        ListElement { name: "img03"; image: "03.png"; enable: true }
        ListElement { name: "img02"; image: "02.png"; enable: true }
        ListElement { name: "img01"; image: "01.png"; enable: true }
    }

    LayerManager {
        id: layerManager
        layersModel: layersData
        x: 20
        y: 300
        //visible: false
    }

    BrushSettings {
        id: brushSettings
        x: 780
        y: 20
        height: 250
        visible: false
    }

    ColorPicker {
        id: colorPicker
        x: 20
        y: 50
        visible: false
        onColorChanged: brush.color = colorPicker.pickColor
    }

    BrushLibrary {
        id: brushLibrary
        x: 780
        y: 320
        visible: false
    }
}



