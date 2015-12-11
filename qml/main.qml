import QtQuick 2.5
import QtQuick.Dialogs 1.2
import QtQuick.Controls 1.3
import QtQuick.Layouts 1.1
import QtQuick.Window 2.2
import QtQuick.Controls.Styles 1.3
import AprilBrush 1.0
import "main"
import "components"
import "dockers"
import "../js/settings.js" as Settings
import "../3rdparty/font-awesome/fontawesome.js" as FontAwesome

ApplicationWindow {
    id: mainRoot
//    title: "AprilBrush - " + fileName + (isDirty ? " [*]" : "") + " @ " + Math.round(canvas3DArea.zoom * 100) + "%"

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
            // ATTENTION! Uses dependencies from private code of QtQuick.Controls!
            // Hack needs to prevent focus catching by MenuBar when Alt pressed
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

    FontLoader {
        source: "qrc:/3rdparty/font-awesome/fontawesome-webfont.ttf"
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

    SplitView {
        anchors.fill: parent

        TabView {
            id: tabView
            Layout.fillWidth: true
            Layout.margins: 5
            height: parent.height
        }

        SplitView {
            width: 200
            height: parent.height
            Layout.minimumWidth: 150
            orientation: Qt.Vertical

            Label {
                font.pointSize: 15
                font.family: "FontAwesome"
                text: FontAwesome.Icon.Plus
            }
        }
    }

    CanvasItem {
        id: canvasItem
//        anchors.fill: parent
    }

//    Canvas3DArea {
//        id: canvas3DArea
//        anchors.fill: parent
//    }

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
