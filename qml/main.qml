import QtQuick 2.0
import QtQuick.Window 2.0
import BrushEngine 1.0
import OpenRaster 1.0
import ImageProcessor 1.0
import "components"
import "utils.js" as Utils
import "undo.js" as Undo


Rectangle {
    id: main
    property size imageSize: Qt.size(Screen.width, Screen.height)
    property bool layerManagerVisible: true
    property point layerManagerPos: Qt.point(20, 300)
    property size layerManagerSize: Qt.size(200, 200)
    property bool undoManagerVisible: true
    property point undoManagerPos: Qt.point(750, 350)
    property size undoManagerSize: Qt.size(200, 200)
    property bool eraserMode: false

    property variant currentPageItem: pageManager.pagesView.currentItem
    property int currentPageIndex: pageManager.pagesView.currentIndex
    /*
    property variant currentLayerModel: currentPageIndex >= 0 ? (pagesModel.get(currentPageIndex).layerModel.count > 0 ?
                                                                 pagesModel.get(currentPageIndex).layerModel : null) : null*/
    property int layerIdCounter: 0
    property string currentLayerId

    onImageSizeChanged: if (imageSize.width) Utils.addPage()

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
        eraser: eraserMode
        layerId: currentLayerId
        imageProcessor: imgProcessor
        onPaintDone: currentPageItem.canvasArea.pathView.currentItem.update(rect)
    }

    ImageProcessor {
        id: imgProcessor
    }

    OpenRaster {
        id: openRaster
        imageProcessor: imgProcessor
    }

    ListModel {
        id: pagesModel
        objectName: "pagesModel"
    }

    PageManager {
        id: pageManager
        z: 1
        width: 600
        height: 34
        anchors.horizontalCenter: parent.horizontalCenter
        //objectName: "page"
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

    FileDialog {
        id: fileDialog
        z: 5
        openMode: false
        visible: false
        onClicked: {
            openMode ? Utils.openOra() : Utils.saveAsOra()
        }
        //onVisibleChanged: visible === false ?
    }
}
