import QtQuick 2.4
import QtQuick.Dialogs 1.2
import QtQuick.Controls 1.3
import QtQuick.Layouts 1.1
import QtQuick.Window 2.2
import QtQuick.Controls.Styles 1.3
import ABLib 1.0
import "settings.js" as Settings
import "main"
import "components"

ApplicationWindow {
    id: mainRoot
    title: "AprilBrush - " + fileName + (isDirty ? " [*]" : "") + " @ " + Math.round(canvasArea.zoom * 100) + "%"

    property string version: "0.3"
    property size imageSize: Qt.size(Screen.width, Screen.height)
    property alias sysPalette: sysPalette
    property bool isDirty: false
    property bool isEraser: brushSettings.eraser > 50
    readonly property int currentLayerIndex: layerManager.layerView.currentIndex
    property string fileName
    property string oraPath
    width: 1230
    height: 655

    menuBar: MainMenu {
        id: mainMenu
        Component.onCompleted: {
            // ОСТОРОЖНО! Используется зависимость от внутреннего кода QtQuick.Controls!
            // при открытом меню нажатие клавиш принимается только там, поэтому нужно передать их оттуда дальше
            __contentItem.Keys.forwardTo = [mainRoot]
        }
    }


    Component.onCompleted: {
        if (!Settings.loadSettings(mainRoot)) {
            x = (Screen.width - width) / 2
            y = (Screen.height - height) / 2
        }

        visible = true
        newImage()
    }

    onClosing: Settings.saveSettings(mainRoot)

    function newImage() {
        fileName = "Untitled"
        oraPath = ""
        layerManager.layerNameIndexCounter = 1
        layerModel.clear()
        layerManager.addLayer()
        undoManager.clear()
    }

    SystemPalette {
        id: sysPalette
        colorGroup: SystemPalette.Active
    }

    ListModel { id: layerModel }
    ListModel { id: undoModel }

    Actions { id: actions}

    CoreLib {
        id: coreLib
        window: mainRoot
    }

    BrushEngine {
        id: brushEngine
    }

    CanvasArea {
        id: canvasArea
        anchors.fill: parent
    }

    ColorPicker {
        id: colorPicker
        x: 10
        y: 10
    }

    LayerManager {
        id: layerManager
        x: 10
        y: 215
    }

    BrushSettings {
        id: brushSettings
        x: 1020
        y: 10
    }

    BrushLibrary {
        id: brushLibrary
        x: 1020
        y: 215
    }

    UndoManager {
        id: undoManager
        x: 1020
        y: 425
    }

    ColorDialog {
        id: colorDialog
        onAccepted: {
            canvasArea.bgColor = color
            isDirty = true
        }
    }

    Item {
        property alias mainX: mainRoot.x
        property alias mainY: mainRoot.y
        property alias mainWidth: mainRoot.width
        property alias mainHeight: mainRoot.height
        property var storage: ["mainWidth", "mainHeight", "mainX", "mainY"]
        objectName: "commonStorage"
    }
}

/*

    Component {
        id: exportCanvas
        Canvas {
            signal finished()
            width: imageSize.width
            height: imageSize.height
            onAvailableChanged: {
                for (var i = layerModel.count - 1; i > -1; i--) {
                    var canvas = layerModel.get(i).canvas
                    var image = canvas.getContext("2d").getImageData(0, 0, width, height)
                    getContext("2d").drawImage(canvas, 0, 0)
                }
                finished()
            }
        }
    }

    Canvas {
        id: dab
        width: brushSettings.size
        height: brushSettings.size
        visible: false
        antialiasing: true
        smooth: false

        onAvailableChanged: requestPaint()

        onPaint: {
            var ctx = getContext("2d")
            ctx.save()
            ctx.clearRect(0, 0, width, height)

            var originX = width / 2
            var originY = width / 2

            ctx.translate(originX, originY)
            ctx.rotate(brushSettings.angle / 180 * Math.PI)
            ctx.scale(1.0, brushSettings.roundness / 100)
            ctx.translate(-originX, -originY)

            var color = Qt.rgba(colorPicker.color.r, colorPicker.color.g, colorPicker.color.b, brushSettings.flow / 100)
            var gradient = ctx.createRadialGradient(width / 2, height / 2, 0, width / 2, height / 2, width / 2)
            gradient.addColorStop(0, color);
            gradient.addColorStop(brushSettings.hardness / 100, color);
            gradient.addColorStop(1, Qt.rgba(colorPicker.color.r, colorPicker.color.g, colorPicker.color.b, brushSettings.hardness / 100 < 1 ? 0 : brushSettings.flow / 100));

            ctx.ellipse(0, 0, width, width)
            ctx.fillStyle = gradient
            ctx.fill()

            ctx.restore();
        }
    }

    Canvas {
        id: pickCanvas
        width: 1
        height: 1
        visible: false
    }


*/
