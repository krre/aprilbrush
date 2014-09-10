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
import "style"

ApplicationWindow {
    id: mainRoot
    title: "AprilBrush"
    property string version: "0.2"
    property size imageSize: Qt.size(Screen.width, Screen.height)
    property CanvasArea currentTab: tabView.count > 0 ? tabView.getTab(tabView.currentIndex).item : null
    property ListModel layerModel: currentTab ? currentTab.layerModel : null
    property ListModel undoModel: currentTab ? currentTab.undoModel : null
    property real pressure: 1
    property alias sysPalette: sysPalette
    property bool isEraser: brushSettings.eraser > 50
    readonly property int currentLayerIndex: currentTab ? layerManager.layerView.currentIndex : -1

    width: 1000
    height: 600
    visible: true

    menuBar: MainMenu {}
    toolBar: MainToolBar { id: toolBar }
//    statusBar: MainStatusBar { id: statusBar }

    Component.onCompleted: {
        Settings.loadSettings(mainRoot)
        actions.newImageAction.trigger()
    }

    onClosing: Settings.saveSettings(mainRoot)

    SystemPalette {
        id: sysPalette
        colorGroup: SystemPalette.Active
    }

    Connections {
        target: PointerEater
        onPressure: mainRoot.pressure = pressure
    }

    Actions { id: actions}

    CoreLib {
        id: coreLib
        window: mainRoot
    }
    FileDialogBase { id: fileDialog }

    About { id: about }

    TabView {
        id: tabView
        property int prevIndex: 0
        anchors.fill: parent
        style: MainTabViewStyle {}
        onCurrentIndexChanged: {
            var prevTab = tabView.getTab(prevIndex).item
            prevTab.savedLayerIndex = layerManager.layerView.currentIndex
            prevTab.savedUndoIndex = undoManager.undoView.currentIndex
            prevIndex = currentIndex
        }
    }

    ColorPicker {
        id: colorPicker
        relativeX: 20
        relativeY: 100
        onColorChanged: dab.requestPaint()
    }

    ColorDialog {
        id: colorDialog
        onAccepted: currentTab.bgColor = color
    }

    LayerManager {
        id: layerManager
        relativeX: 20
        relativeY: 340
    }

    BrushSettings {
        id: brushSettings
        relativeX: mainRoot.width - width - 30
        relativeY: 100
    }

    BrushLibrary {
        id: brushLibrary
        relativeX: mainRoot.width - width - 30
        relativeY: 340
    }

    UndoManager {
        id: undoManager
        relativeX: mainRoot.width - width - 30
        relativeY: 340
    }

    Component {
        id: canvasArea
        CanvasArea {}
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
        width: brushSettings.diameter
        height: brushSettings.diameter
        visible: false
        antialiasing: true

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


    Item {
        property alias mainX: mainRoot.x
        property alias mainY: mainRoot.y
        property alias mainWidth: mainRoot.width
        property alias mainHeight: mainRoot.height
        property var storage: ["mainWidth", "mainHeight", "mainX", "mainY"]
        objectName: "commonStorage"
    }
}
