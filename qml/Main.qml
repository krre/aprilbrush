import QtQuick 2.5
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
    title: "AprilBrush - " + fileName + (isDirty ? " [*]" : "") + " @ " + Math.round(canvas3DArea.zoom * 100) + "%"

    property string version: "0.3"
    property size imageSize: Qt.size(Screen.width, Screen.height)
    property alias sysPalette: sysPalette
    property bool isDirty: false
    property bool isEraser: brushSettings.eraser > 50
    readonly property int currentLayerIndex: layerManager.layerView.currentIndex
    property string fileName: qsTr("Untitled")
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
        layerManager.addLayer()
        undoManager.clear()
    }

    onClosing: Settings.saveSettings(mainRoot)

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

    Canvas3DArea {
        id: canvas3DArea
        anchors.fill: parent
    }

//    CanvasArea {
//        id: canvasArea
//        anchors.fill: parent
//    }

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
