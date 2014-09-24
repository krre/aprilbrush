/* AprilBrush - Digital Painting Software
 * Copyright (C) 2012-2014 Vladimir Zarypov <krre31@gmail.com>
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

import QtQuick 2.3
import QtQuick.Dialogs 1.2
import QtQuick.Controls 1.2
import QtQuick.Layouts 1.1
import QtQuick.Window 2.0
import QtQuick.Controls.Styles 1.2
import ABLib 1.0
import "settings.js" as Settings
import "main"

ApplicationWindow {
    id: mainRoot
    title: "AprilBrush - " + fileName + (isDirty ? " [*]" : "") + " @ " + Math.round(canvasArea.zoom * 100) + "%"

    property string version: "0.3"
    property size imageSize: Qt.size(Screen.width, Screen.height)
    property real pressure: 1
    property alias sysPalette: sysPalette
    property bool isDirty: false
    property bool isEraser: brushSettings.eraser > 50
    readonly property int currentLayerIndex: layerManager.layerView.currentIndex
    property string fileName
    property string oraPath
    property bool isCtrlPressed: false

    x: 50
    y: 50
    width: 1000
    height: 600
    visible: true

    menuBar: MainMenu {}

    Component.onCompleted: {
        if (!Settings.loadSettings(mainRoot)) {
            colorPicker.visible = true
            layerManager.visible = true
            brushSettings.visible = true
            brushLibrary.visible = true
            undoManager.visible = true
        }

        newImage()
        mainRoot.onWidthChanged.connect(function resTransform() {
            canvasArea.resetTransform() // after changing window on load settings
            mainRoot.onWidthChanged.disconnect(resTransform)
        })
    }

    onClosing: Settings.saveSettings(mainRoot)

    function newImage() {
        fileName = "Untitled"
        oraPath = ""
        layerManager.layerNameIndexCounter = 1
        layerModel.clear()
        layerManager.addBackground()
        layerManager.addLayer()
        undoManager.clear()
        canvasArea.resetTransform() // after adding new tab on runnging application
        mainRoot.onWidthChanged.connect(function resTransform() {
            canvasArea.resetTransform() // after adding new tab on start application
            canvasArea.onWidthChanged.disconnect(resTransform)
        })
    }

    SystemPalette {
        id: sysPalette
        colorGroup: SystemPalette.Active
    }

    ListModel { id: layerModel }
    ListModel { id: undoModel }

    Connections {
        target: PointerEater
        onPressure: mainRoot.pressure = pressure
    }

    Actions { id: actions}

    CoreLib {
        id: coreLib
        window: mainRoot
    }

    BrushEngine {
        id: brushEngine
    }

    FileDialogBase { id: fileDialog }

    About { id: about }

    CanvasArea {
        id: canvasArea
        anchors.fill: parent
    }

    ColorPicker {
        id: colorPicker
        x: 75
        y: 110
        onColorChanged: dab.requestPaint()
    }

    LayerManager {
        id: layerManager
        x: 75
        y: 365
    }

    BrushSettings {
        id: brushSettings
        x: 810
        y: 110
    }

    BrushLibrary {
        id: brushLibrary
        x: 810
        y: 365
    }

    UndoManager {
        id: undoManager
        x: 580
        y: 110
    }

    ColorDialog {
        id: colorDialog
        onAccepted: {
            canvasArea.bgColor = color
            isDirty = true
        }
    }

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

    Item {
        property alias mainX: mainRoot.x
        property alias mainY: mainRoot.y
        property alias mainWidth: mainRoot.width
        property alias mainHeight: mainRoot.height
        property var storage: ["mainWidth", "mainHeight", "mainX", "mainY"]
        objectName: "commonStorage"
    }
}
