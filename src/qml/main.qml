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

import QtQuick 2.1
import QtQuick.Dialogs 1.0
import QtQuick.Controls 1.0
import QtQuick.Layouts 1.1
import QtQuick.Window 2.0
import ABLib 1.0
import "components"
import "settings.js" as Settings
import "utils.js" as Utils
import "undo.js" as Undo
import "style.js" as Style

Rectangle {
    id: mainRoot
    property real pressure: 0
    property var palette: Style.defaultStyle()
    property bool cornerHover: rightTopCorner.containsMouse | leftBottomCorner.containsMouse
    property var storage: { var list = Settings.defaultStorage(); list.push("eraserMode"); return list }

    property int newTabCounter: 0

//    property var tabContent: tabView.count > 0 ? tabView.getTab(tabView.currentIndex).item : 0
//    property var layerModel: tabView.count > 0 ? tabContent.layerModel : []
//    property var undoModel: tabView.count > 0 ? tabContent.undoModel : []

    property size imageSize: Qt.size(Screen.width, Screen.height)
    property bool eraserMode: false
    property int layerIdCounter: 0
    property string currentLayerId

    width: 1000
    height: 600

    Component.onCompleted: {
        Settings.loadSettings()
//        Utils.addTab()

    }
    Component.onDestruction: Settings.saveSettings()

    Connections {
        target: PointerEater
        onPressure: mainRoot.pressure = pressure
        onPressed: type == 0 ? mainRoot.pressure = 1 : mainRoot.pressure = 0
    }

    MouseArea {
        id: rightTopCorner
        width: 50
        height: 50
        anchors.right: parent.right
        anchors.top: pageManager.bottom
        preventStealing: true
        hoverEnabled: true
        onDoubleClicked: pageManager.collapse = !pageManager.collapse
    }

    MouseArea {
        id: leftBottomCorner
        width: 50
        height: 50
        anchors.left: parent.left
        anchors.bottom: parent.bottom
        preventStealing: true
        hoverEnabled: true
        onDoubleClicked: canvas.clear()
    }

    Keys.onSpacePressed: flickable.interactive = !flickable.interactive
    Keys.onPressed: {
        if (event.key === Qt.Key_Plus) {
            canvas.scale *= 1.1
        } else if (event.key === Qt.Key_Minus) {
            canvas.scale /= 1.1
        } else if (event.key === Qt.Key_0) {
            canvas.scale = 1
        }
    }

    Flickable {
        id: flickable
        anchors.fill: parent
        contentWidth: canvas.width
        contentHeight: canvas.height
        interactive: false

        Canvas {
            id: canvas
            property point lastDrawPoint
            width: imageSize.width
            height: imageSize.height
            anchors.centerIn: parent
    //        antialiasing: true
            smooth: false
            focus: true

            property real diameter: brushSettings.brushModel.children[0].value
            property real opaque: brushSettings.brushModel.children[1].value / 100
            property real hardness: brushSettings.brushModel.children[2].value / 100
            property real spacing: brushSettings.brushModel.children[3].value / 100

            property color fillStyle: "#ffffff"

            onAvailableChanged: clear()

            function clear() {
                var ctx = canvas.getContext("2d")
                ctx.save()
                ctx.fillStyle = canvas.fillStyle
                ctx.fillRect(0, 0, width, height)
                ctx.restore();
                requestPaint()
            }

            MouseArea {
                property real deltaDab: Math.max(canvas.spacing * canvas.diameter, 1)
                property var points: []
                property bool linearMode: false
                anchors.fill: parent
                propagateComposedEvents: true
                enabled: !flickable.interactive

                function bezierCurve(start, control, end, t) {
                    var x, y
                    // linear bezier curve
                    if (!control) {
                        x = (1 - t) * start.x + t * end.x
                        y = (1 - t) * start.y + t * end.y
                    }
                    // quad bezier curve
                    else {
                        x = Math.pow((1 - t), 2) * start.x + 2 * t * (1 - t) * control.x + t * t * end.x
                        y = Math.pow((1 - t), 2) * start.y + 2 * t * (1 - t) * control.y + t * t * end.y
                    }

                    return Qt.point(x, y)
                }

                onPressed: {
                    var point = Qt.point(mouseX, mouseY)
                    canvas.lastDrawPoint = point
                    if (!cornerHover) {
                        canvas.drawDab(point)
                    }
                    points = []
                    points.push(point)
                }
                onPositionChanged: {
                    var currentPoint = Qt.point(mouseX, mouseY)
                    var startPoint = canvas.lastDrawPoint
                    var currentSpacing = Math.sqrt(Math.pow(currentPoint.x - startPoint.x, 2) + Math.pow(currentPoint.y - startPoint.y, 2))
                    var numDabs = Math.floor(currentSpacing / deltaDab)
                    if (numDabs >= 1) {

                        if (points.length == 1 || numDabs < 3 || linearMode) {
                            var endPoint = currentPoint
                        } else {
                            var controlPoint = points[points.length - 1]
                            endPoint = Qt.point((controlPoint.x + currentPoint.x) / 2, (controlPoint.y + currentPoint.y) / 2)
                        }

                        var deltaT = 1 / numDabs
                        var betweenPoint = startPoint
                        var t = deltaT
                        var diff
                        while (t > 0 && t <= 1) {
                            var point = bezierCurve(startPoint, controlPoint, endPoint, t)
                            var deltaPoint = Math.sqrt(Math.pow(point.x - betweenPoint.x, 2) + Math.pow(point.y - betweenPoint.y, 2))
                            // check on bezier loop
                            if (diff && Math.abs(deltaPoint - deltaDab) > Math.abs(diff)) { break; }
                            diff = deltaPoint - deltaDab
                            if (Math.abs(diff <= 0.5)) {
                                canvas.drawDab(point)
                                diff = undefined
                                betweenPoint = point
                                t += deltaT
                            } else {
                                t -= diff / deltaDab * deltaT
                            }
                        }
                        points.push(currentPoint)
                        canvas.lastDrawPoint = betweenPoint
                    }
                }
            }

            function drawDab(point) {
    //            console.log(point)
                var dabCanvas = dab.getContext("2d").getImageData(0, 0, dab.width, dab.height)
                var ctx = canvas.getContext("2d")
                ctx.save()
                var x = point.x - dab.width / 2
                var y = point.y - dab.height / 2
    //            console.log(x, y)
                ctx.globalAlpha = (x - Math.floor(x) + y - Math.floor(y)) / 2
                ctx.drawImage(dabCanvas, Math.floor(x), Math.floor(y))
    //            console.log(ctx.globalAlpha, Math.floor(x), Math.floor(y))

                ctx.globalAlpha = (Math.floor(x + 1) - x + Math.floor(y + 1) - y) / 2
                ctx.drawImage(dabCanvas, Math.floor(x + 1), Math.floor(y + 1))
    //            console.log(ctx.globalAlpha, Math.floor(x + 1), Math.floor(y + 1))

                ctx.globalAlpha = (x - Math.floor(x) + Math.floor(y + 1) - y) / 2
                ctx.drawImage(dabCanvas, Math.floor(x), Math.floor(y + 1))
    //            console.log(ctx.globalAlpha, Math.floor(x), Math.floor(y + 1))

                ctx.globalAlpha = (Math.floor(x + 1) - x + y - Math.floor(y)) / 2
                ctx.drawImage(dabCanvas, Math.floor(x + 1), Math.floor(y))
    //            console.log(ctx.globalAlpha, Math.floor(x + 1), Math.floor(y))


    //            ctx.drawImage(dabCanvas, point.x - dab.width / 2, point.y - dab.height / 2)
                ctx.restore()
                markDirty(point.x - dab.width / 2, point.y - dab.height / 2, dab.width, dab.height)
            }
        }
    }

    Canvas {
        id: dab
        width: canvas.diameter
        height: canvas.diameter
        visible: false
        antialiasing: true

        onPaint: {
            var ctx = dab.getContext("2d")
            ctx.clearRect(0, 0, width, height)
            var color = Qt.rgba(colorPicker.color.r, colorPicker.color.g, colorPicker.color.b, canvas.opaque)
            var gradient = ctx.createRadialGradient(width / 2, height / 2, 0, width / 2, height / 2, width / 2)
            gradient.addColorStop(0, color);
            gradient.addColorStop(canvas.hardness, color);
            gradient.addColorStop(1, Qt.rgba(colorPicker.color.r, colorPicker.color.g, colorPicker.color.b, canvas.hardness < 1 ? 0 : canvas.opaque));

            ctx.ellipse(0, 0, width, height)
            ctx.fillStyle = gradient
            ctx.fill()

            ctx.restore();
            markDirty(0, 0, width, height)
        }
    }

    PageManager {
        id: pageManager
        width: parent.width
//        height: 0
    }

    TopBar {
        id: topBar
        property var storage: ["visible"]
        objectName: "topBar"
        width: parent.width
        anchors.top: pageManager.bottom

    }

    ColorPicker {
        id: colorPicker
        x: 25
        y: 25
        onColorChanged: dab.requestPaint()
    }

    BrushSettings {
        id: brushSettings
        x: 500
        y: 25
        onSettingsChanged: dab.requestPaint()
    }

    BrushLibrary {
        id: brushLibrary
        x: 500
        y: 200
    }

    Item {
        property alias mainWidth: mainRoot.width
        property alias mainHeight: mainRoot.height
        property var storage: ["mainWidth", "mainHeight"]
        objectName: "commonStorage"
    }

    /*

    TabView {
        id: tabView
        property alias tabComponent: tabComponent
        anchors.fill: parent
        visible: count > 0
        focus: true

        onCurrentIndexChanged: tabContent.canvasArea.pathView.currentItem.update()

        Keys.onPressed: {
            event.accepted = true;
            if (event.key === Qt.Key_Tab) {
                if (!event.isAutoRepeat) {
                    dock.visible = !dock.visible
                }
            }
        }

        Component {
            id: tabComponent

            Item {
                property alias canvasArea: canvasArea
                property alias layerModel: layerModel
                property alias undoModel: undoModel
                property int newLayerCounter: 0

                CanvasArea {
                    id: canvasArea
                }

                ListModel {
                    id: layerModel
                }

                ListModel {
                    id: undoModel
                }
            }
        }
    }

    Item {
        id: dock
        width: 650
        height: 600
        visible: false
        anchors.centerIn: parent

        ColumnLayout {
            anchors.left: parent.left
            width: 200
            height: parent.height
            spacing: 0

            LayerManager {
                id: layerManager
                Layout.fillHeight: true
            }

            BrushSettings {
                id: brushSettings
                Layout.fillHeight: true
            }
        }

        ColorPicker {
            id: colorPicker
            anchors.centerIn: parent
            color: Utils.hsvToHsl(settings.colorPicker.color.h,
                                  settings.colorPicker.color.s,
                                  settings.colorPicker.color.v)
        }

        ColumnLayout {
            anchors.right: parent.right
            width: 200
            height: parent.height
            spacing: 0

            UndoManager {
                id: undoManager
                Layout.fillHeight: true
            }

            BrushLibrary {
                id: brushLibrary
                Layout.fillHeight: true
            }
        }
    }

    menuBar: MenuBar {
        Menu {
            title: qsTr("File")
            MenuItem {
                text: qsTr("New")
                shortcut: "Ctrl+N"
                onTriggered: Utils.addTab()
            }
            MenuItem {
                text: qsTr("Open...")
                shortcut: "Ctrl+O"
                onTriggered: Utils.createDynamicObject(mainRoot, "FileDialog.qml", { mode: 0 })
            }
            MenuItem {
                text: qsTr("Save")
                shortcut: "Ctrl+S"
                enabled: tabView.count > 0
            }
            MenuItem {
                text: qsTr("Save As...")
                shortcut: "Ctrl+Shift+S"
                enabled: tabView.count > 0
                onTriggered: Utils.createDynamicObject(mainRoot, "FileDialog.qml", { mode: 1 })
            }
            MenuItem {
                text: qsTr("Export...")
                shortcut: "Ctrl+E"
                enabled: tabView.count > 0
                onTriggered: Utils.createDynamicObject(mainRoot, "FileDialog.qml", { mode: 2 })
            }
            MenuItem {
                text: qsTr("Close")
                shortcut: "Ctrl+W"
                onTriggered: {
                    tabView.removeTab(tabView.currentIndex)
                    if (!tabView.count)
                        newTabCounter = 0
                }
                enabled: tabView.count > 0
            }
            MenuSeparator { }
            MenuItem {
                text: qsTr("Quit")
                shortcut: "Ctrl+Q"
                onTriggered: mainRoot.close()
            }
        }

        Menu {
            title: qsTr("Edit")
            MenuItem {
                text: qsTr("Undo")
                shortcut: "Ctrl+Z"
                enabled: (tabView.count > 0) && (undoManager.undoView.currentIndex > 0)
                onTriggered: undoManager.undoView.listView.decrementCurrentIndex()
            }
            MenuItem {
                text: qsTr("Redo")
                shortcut: "Ctrl+Y"
                enabled: (tabView.count > 0) && (undoManager.undoView.currentIndex < undoManager.undoView.listView.count - 1)
                onTriggered: undoManager.undoView.listView.incrementCurrentIndex()
            }
        }

        Menu {
            title: qsTr("Canvas")
            MenuItem {
                text: qsTr("Clear")
                onTriggered: {
                    undoManager.add(new Undo.clear())
                    brushEngine.clear()
                    tabContent.canvasArea.pathView.currentItem.update()
                }
                shortcut: "Delete"
                enabled: tabView.count > 0
            }

            MenuItem {
                text: qsTr("Fill Color")
                onTriggered: {
                    undoManager.add(new Undo.fillColor())
                }
                shortcut: "F"
                enabled: tabView.count > 0
            }
        }

        Menu {
            title: qsTr("Brushes")

            MenuItem {
                text: qsTr("Brush")
                onTriggered: {
                    eraserMode = false
                }
                shortcut: "B"
                enabled: tabView.count > 0
            }

            MenuItem {
                text: qsTr("Eraser")
                onTriggered: {
                    eraserMode = true
                }
                shortcut: "E"
                enabled: tabView.count > 0
            }
        }



        Menu {
            title: qsTr("Help")
            MenuItem {
                text: qsTr("About...")
                onTriggered: Utils.createDynamicObject(mainRoot, "About.qml")
            }
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
        jitter: brushSettings.jitter.value
        eraser: eraserMode
        layerId: currentLayerId
        imageProcessor: imgProcessor
        onPaintDone: tabContent.canvasArea.pathView.currentItem.update()
    }

    ImageProcessor {
        id: imgProcessor
        layerId: currentLayerId
    }

    OpenRaster {
        id: openRaster
        imageProcessor: imgProcessor
    }
    */

    CoreLib {
        id: coreLib
    }
}

