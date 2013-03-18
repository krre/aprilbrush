import QtQuick 2.0
import QtQuick.Window 2.0
import BrushEngine 1.0
import "components"
import "utils.js" as Utils

Rectangle {
    id: main
    property size imageSize: Qt.size(Screen.width, Screen.height)
    property bool layerManagerVisible: true
    property bool undoManagerVisible: true
    property point layerManagerPos: Qt.point(20, 300)
    property point undoManagerPos: Qt.point(750, 350)

    width: 1000
    height: 600
    color: "lightgray"

    Brush {
        id: brush
        color: "black"
        size: brushSettings.size
        spacing: brushSettings.spacing
        hardness: brushSettings.hardness
        opacity: brushSettings.opacityBrush
        roundness: brushSettings.roundness
        angle: brushSettings.angle
        source: pageManager.pagesView.currentItem.canvasArea.pathView.currentItem
    }

    PageManager {
        id: pageManager
        z: 1
        width: 600
        height: 34
        anchors.horizontalCenter: parent.horizontalCenter

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
        y: 50
        z: 2
        height: 250
        //visible: false

    }

    ColorPicker {
        id: colorPicker
        x: 20
        y: 50
        z: 3
        defaultHeight: 220
        //visible: false
        onColorChanged: brush.color = colorPicker.pickColor

    }

    BrushLibrary {
        id: brushLibrary
        x: 780
        y: 320
        z: 4
        visible: false

    }
}



