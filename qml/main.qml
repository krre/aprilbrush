import QtQuick 2.0
import QtQuick.Window 2.0
import BrushEngine 1.0
import OpenRaster 1.0
import ImageProcessor 1.0
import CoreLib 1.0
import "components"
import "settings.js" as Settings
import "utils.js" as Utils
import "undo.js" as Undo

Rectangle {
    id: main

    property var settings
    // Settings property don't works for Layer Manager and Undo Manager
    property vector3d layerManagerPos
    property size layerManagerSize
    property bool layerManagerVisible
    property vector3d undoManagerPos
    property size undoManagerSize
    property bool undoManagerVisible

    property size imageSize: Qt.size(Screen.width, Screen.height)
    property bool eraserMode: false
    property variant currentPageItem: pageManager.pagesView.currentItem
    property int currentPageIndex: pageManager.pagesView.currentIndex
    property int layerIdCounter: 0
    property string currentLayerId

    property bool dockMode: false

    Component.onCompleted: {
        Settings.loadSettings()
        main.width = settings.mainWindow.width
        main.height = settings.mainWindow.height

        layerManagerPos.x = settings.layerManager.position.x
        layerManagerPos.y = settings.layerManager.position.y
        layerManagerPos.z = settings.layerManager.position.z
        layerManagerSize.width = settings.layerManager.size.width
        layerManagerSize.height = settings.layerManager.size.height
        layerManagerVisible = settings.layerManager.visible

        undoManagerPos.x = settings.undoManager.position.x
        undoManagerPos.y = settings.undoManager.position.y
        undoManagerPos.z = settings.undoManager.position.z
        undoManagerSize.width = settings.undoManager.size.width
        undoManagerSize.height = settings.undoManager.size.height
        undoManagerVisible = settings.undoManager.visible

    }
    Component.onDestruction: Settings.saveSettings()

    onImageSizeChanged: if (imageSize.width && imageSize.height) Utils.addPage()

    color: "lightgray"

    Keys.onPressed: {
        if (event.modifiers & Qt.AltModifier) {
            dockMode = true
        }
    }

    Keys.onReleased: {
        if (Qt.AltModifier) {
            dockMode = false
        }
    }

    BrushEngine {
        id: brushEngine
        color: colorPicker.color
        size: brushSettings.size.value
        spacing: brushSettings.spacing.value
        hardness: brushSettings.hardness.value
        opacity: brushSettings.opaque.value
        roundness: brushSettings.roundness.value
        angle: brushSettings.angle.value
        eraser: eraserMode
        layerId: currentLayerId
        imageProcessor: imgProcessor
        onPaintDone: currentPageItem.canvasArea.pathView.currentItem.update(rect)
    }

    ImageProcessor {
        id: imgProcessor
        layerId: currentLayerId
    }

    OpenRaster {
        id: openRaster
        imageProcessor: imgProcessor
    }

    CoreLib {
        id: coreLib
    }

    ListModel {
        id: pageModel
    }

    Item {
        id: workArea
        anchors.fill: parent

        PageManager {
            id: pageManager
            z: 1
            anchors.horizontalCenter: parent.horizontalCenter
        }

        BrushSettings {
            id: brushSettings
            x: settings.brushSettings.position.x
            y: settings.brushSettings.position.y
            z: settings.brushSettings.position.z
            width: settings.brushSettings.size.width
            height: settings.brushSettings.size.height
            visible: settings.brushSettings.visible
        }

        ColorPicker {
            id: colorPicker
            x: settings.colorPicker.position.x
            y: settings.colorPicker.position.y
            z: settings.colorPicker.position.z
            width: settings.colorPicker.size.width
            height: settings.colorPicker.size.height
            color: Utils.hsvToHsl(settings.colorPicker.color.h,
                                  settings.colorPicker.color.s,
                                  settings.colorPicker.color.v)
            visible: settings.colorPicker.visible

            defaultHeight: 220
        }

        BrushLibrary {
            id: brushLibrary
            x: settings.brushLibrary.position.x
            y: settings.brushLibrary.position.y
            z: settings.brushLibrary.position.z
            width: settings.brushLibrary.size.width
            height: settings.brushLibrary.size.height
            visible: settings.brushLibrary.visible
        }

        FileDialog {
            id: fileDialog
            z: 5
            visible: false
            onClicked: {
                switch (mode) {
                    case 0: Utils.openOra(); break
                    case 1: Utils.saveAsOra(); break
                    case 2: Utils.exportPng(); break
                }
                currentPageItem.canvasArea.focusBind = false
                currentPageItem.canvasArea.focus = true
                currentPageItem.canvasArea.focusBind = true
                visible = false
            }
        }
    }

    Dock {
        anchors.verticalCenter: parent.verticalCenter
        anchors.horizontalCenter: parent.horizontalCenter
        visible: dockMode
    }
}

