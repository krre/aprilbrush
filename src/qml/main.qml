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
    title: "AprilBrush" + (currentTab ?
             " - " + currentTab.fileName + (currentTab.isDirty ? " [*]" : "") + " @ " + Math.round(currentTab.zoom * 100) + "%"
             : "")

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
            // Hack needs to prevent focus catching by MenuBar when Alt modifier is pressed
            __contentItem.Keys.forwardTo = [mainRoot]
        }
    }

    Component.onCompleted: {
        x = Settings.value("Main", "x", (Screen.width - width) / 2)
        y = Settings.value("Main", "y", (Screen.height - height) / 2)

        Utils.loadRecentFiles()

        Utils.movePanelToDocker(colorPicker, topDock)
        Utils.movePanelToDocker(undoManager, topDock)
        Utils.movePanelToDocker(layerManager, bottomDock)
        Utils.movePanelToDocker(brushSettings, bottomDock)
        Utils.movePanelToDocker(brushLibrary, bottomDock)

        visible = true

        Utils.newTab()
    }

    onClosing: {
        Settings.setValue("Main", "x", x)
        Settings.setValue("Main", "y", y)
        Settings.setValue("Main", "width", width)
        Settings.setValue("Main", "height", height)

        Settings.setValue("Main", "dockerSplit.width", dockerSplit.width)
        Settings.setValue("Main", "topDock.height", topDock.height)

        Utils.saveRecentFiles()
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

    SplitView {
        anchors.fill: parent

        TabView {
            id: tabView
            Layout.fillWidth: true
            Layout.margins: 5
            height: parent.height
            clip: true
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

    ColorPicker {
        id: colorPicker
        onColorChanged: BrushEngine.color = color
    }

    UndoManager {
        property bool isNewModel: false
        id: undoManager
        enabled: currentTab

        onCurrentIndexChanged: {
            if (!(isNewModel && currentIndex == 0)) {
                currentTab.currentUndoIndex = currentIndex
            } else { // tab is changed, need restore layer index
                currentIndex = currentTab.currentUndoIndex
                isNewModel = false
            }
        }
    }

    onUndoModelChanged: undoManager.isNewModel = true

    LayerManager {
        property bool isNewModel: false
        id: layerManager
        enabled: currentTab

        onCurrentIndexChanged: {
            if (!(isNewModel && currentIndex == 0)) {
                currentTab.currentLayerIndex = currentIndex
            } else { // tab is changed, need restore layer index
                currentIndex = currentTab.currentLayerIndex
                isNewModel = false
            }
        }
    }

    onLayerModelChanged: layerManager.isNewModel = true

    BrushSettings {
        id: brushSettings
    }

    BrushLibrary {
        id: brushLibrary
    }
}
