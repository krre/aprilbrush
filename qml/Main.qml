/* AprilBrush - Digital Painting Software
 * Copyright (C) 2012-2015 Vladimir Zarypov <krre31@gmail.com>
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation;
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 */

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

    menuBar: MainMenu { id: mainMenu }

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
//        layerManager.addBackground()
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
        color: colorPicker.color
        size: brushSettings.size
        opacity: brushSettings.opaque
        flow: brushSettings.flow
        hardness: brushSettings.hardness
        spacing: brushSettings.spacing
        roundness: brushSettings.roundness
        angle: brushSettings.angle
        jitter: brushSettings.jitter
        eraser: brushSettings.eraser
        onPainted: canvasArea.canvas.update(rect)
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
