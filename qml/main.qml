import QtQuick 2.0
import QtQuick.Window 2.0
import BrushEngine 1.0
import "components"
import "utils.js" as Utils

Rectangle {
    id: main
    property size imageSize: Qt.size(Screen.width, Screen.height)
    property bool layerManagerVisible: true
    property point layerManagerPos: Qt.point(20, 300)

    width: 1000
    height: 600
    color: "lightgray"

    Brush {
        id: brush
        color: "black"
        size: brushSettings.size
        spacing: brushSettings.spacing
        hardness: brushSettings.hardness
        opacity: brushSettings.opacity_
        roundness: brushSettings.roundness
        angle: brushSettings.angle
        source: pageManager.pagesView.currentItem.canvasArea.pathView.currentItem
    }

    PageManager {
        id: pageManager
        width: 600
        height: 34
        anchors.horizontalCenter: parent.horizontalCenter
        z: 1
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
        z: 2
    }

    ColorPicker {
        id: colorPicker
        x: 20
        y: 50
        //visible: false
        onColorChanged: brush.color = colorPicker.pickColor
        z: 3
    }

    BrushLibrary {
        id: brushLibrary
        x: 780
        y: 320
        visible: false
        z: 4
    }
/*
    UndoManager {
        id: undoManager
        x: 750
        y: 200
        z: 5
    }
    */
}



