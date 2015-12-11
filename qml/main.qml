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
import "../js/utils.js" as Utils

ApplicationWindow {
    id: mainRoot
    title: "AprilBrush"
//    title: "AprilBrush - " + fileName + (isDirty ? " [*]" : "") + " @ " + Math.round(canvas3DArea.zoom * 100) + "%"

    property string version: "0.3"
    property size imageSize: Qt.size(Screen.width, Screen.height)
    property alias sysPalette: sysPalette
    property bool isEraser: brushSettings.eraser > 50
    property WorkArea currentTab: tabView.count > 0 ? tabView.getTab(tabView.currentIndex).item : null
    property ListModel layerModel: currentTab ? currentTab.layerModel : null
    property ListModel undoModel: currentTab ? currentTab.undoModel : null
    width: Settings.value("Main", "width", 800)
    height: Settings.value("Main", "height", 600)

    menuBar: MainMenu {
        id: mainMenu
        Component.onCompleted: {
            // ATTENTION! Uses dependencies from private code of QtQuick.Controls!
            // Hack needs to prevent focus catching by MenuBar when Alt pressed
            __contentItem.Keys.forwardTo = [mainRoot]
        }
    }

    Component.onCompleted: {
        x = Settings.value("Main", "x", (Screen.width - width) / 2)
        y = Settings.value("Main", "y", (Screen.height - height) / 2)

        visible = true
//        layerManager.addLayer()
//        undoManager.clear()

        Utils.movePanelToDocker(colorPicker, topDock)
        Utils.movePanelToDocker(undoManager, topDock)
        Utils.movePanelToDocker(layerManager, bottomDock)
        Utils.movePanelToDocker(brushSettings, bottomDock)
        Utils.movePanelToDocker(brushLibrary, bottomDock)

    }

    onClosing: {
        Settings.setValue("Main", "x", x)
        Settings.setValue("Main", "y", y)
        Settings.setValue("Main", "width", width)
        Settings.setValue("Main", "height", height)

        Settings.setValue("Main", "dockerSplit.width", dockerSplit.width)
        Settings.setValue("Main", "topDock.height", topDock.height)
    }

    onCurrentTabChanged: {
        if (currentTab) {
            layerManager.currentIndex = currentTab.currentLayerIndex
        }
    }

    SystemPalette {
        id: sysPalette
        colorGroup: SystemPalette.Active
    }

    FontLoader {
        source: "qrc:/3rdparty/font-awesome/fontawesome-webfont.ttf"
    }

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
            id: dockerSplit
            width: Settings.value("Main", "dockerSplit.width", 200)
            height: parent.height
            Layout.minimumWidth: 150
            orientation: Qt.Vertical

            TabView {
                id: topDock
                height: Settings.value("Main", "topDock.height", 300)
                Layout.minimumHeight: 200
                frameVisible: false
            }

            TabView {
                id: bottomDock
                Layout.minimumHeight: 200
                frameVisible: false
            }
        }
    }

//    CanvasItem {
//        id: canvasItem
//        anchors.fill: parent
//    }

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

    UndoManager {
        id: undoManager
        x: 1020
        y: 425
        enabled: currentTab
    }

    LayerManager {
        id: layerManager
        x: 10
        y: 215
        onCurrentIndexChanged: {
            currentTab.currentLayerIndex = currentIndex
        }
        enabled: currentTab
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

    ColorDialog {
        id: colorDialog
        onAccepted: {
            canvasArea.bgColor = color
            isDirty = true
        }
    }
}
