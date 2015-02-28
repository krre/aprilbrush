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

import QtQuick 2.4
import QtQuick.Controls 1.3
import ABLib 1.0
import "components"
import "undo.js" as Undo
import "utils.js" as Utils

Item {
    id: root
    property alias canvas: canvasView.currentItem
    property alias canvasView: canvasView
    property color bgColor: "white"
    property bool isPan: false
    property bool isPick: false
    property point grabPoint

    property real zoom: 1.0
    property int mirror: 1
    property real rotation: 0

    onBgColorChanged: layerModel.get(layerModel.count - 1).canvas.clear(bgColor)
    onIsPanChanged: coreLib.setCursorShape(isPan ? "OpenHand" : "Paint", brushSettings.size * zoom)
    onZoomChanged: coreLib.setCursorShape(isPan ? "OpenHand" : "Paint", brushSettings.size * zoom)

    Keys.onPressed: {
        if (event.key === Qt.Key_Space && !event.isAutoRepeat) {
            grabPoint = Qt.point(mouseArea.mouseX, mouseArea.mouseY)
            isPan = true
        }
        if (event.modifiers & Qt.ControlModifier) { isPick = true }
    }

    Keys.onReleased: {
        if (Qt.ControlModifier) { isPick = false }
        if (event.key === Qt.Key_Space && !event.isAutoRepeat) { isPan = false }
    }

    transform: [
        Scale { origin.x: width / 2; origin.y: height / 2; xScale: zoom * mirror; yScale: zoom },
        Rotation { origin.x: width / 2; origin.y: height / 2; angle: rotation }
    ]

    Component.onCompleted: {
        coreLib.addEventFilter(mainRoot)
        forceActiveFocus()
    }

    function resetTransform() {
        zoom = 1
        mirror = 1
        rotation = 0
        content.x = (width - content.width) / 2
        content.y = (height - content.height) / 2
    }

    function zoomIn() {
        if (zoom < 30) zoom *= 1.5
    }

    function zoomOut() {
        if (zoom > 0.01) zoom /= 1.5
    }

    Rectangle {
        id: content
        width: imageSize.width
        height: imageSize.height
        color: bgColor

        ListView {
            id: canvasView
            anchors.fill: parent
            model: layerModel
            spacing: -width
            orientation: ListView.Horizontal
            currentIndex: layerManager.layerView.currentIndex
            interactive: false
            delegate: CanvasItem {
                width: ListView.view.width
                height: ListView.view.height
                z: 1000 - index
                visible: isVisible
                enabled: !isLock
                smooth: false

                Component.onCompleted: {
                    layerModel.set(index, { "canvas": this })
                }
            }
        }

        Connections {
            property bool isTouch: false
            target: TabletEventFilter
            onAction: {
                var x = event.globalX - mainRoot.x - content.x
                var y = event.globalY - mainRoot.y - content.y - mainMenu.__contentItem.height
                var pressure = event.pressure
                if (event.press === true) {
                    isTouch = true
                    brushEngine.setTouch(true, canvas)
                    brushEngine.paint(Qt.point(x, y), pressure)
                } else if (event.release === true) {
                    isTouch = false
                    brushEngine.setTouch(false)
                } else if (isTouch) {
                    brushEngine.paint(Qt.point(x, y), pressure)
                }
            }
        }

        MouseArea {
            id: mouseArea
            anchors.fill: parent
//            enabled: buffer.parent ? buffer.parent.enabled : false
            hoverEnabled: true

            onHoveredChanged: coreLib.setCursorShape(containsMouse ? "Paint" : "Arrow", brushSettings.size * zoom)

            onWheel: {
                if (wheel.modifiers & Qt.ControlModifier) {
                    if (wheel.angleDelta.y > 0) {
                        zoomIn()
                    } else {
                        zoomOut()
                    }
                }
            }

            onPressed: {
                var point = Qt.point(mouseX, mouseY)
                if (isPick) {
                    coreLib.setCursorShape("PickColor", 0)
                    Utils.pickColor(point)
                } else if (!isPan) {
                    if (isEraser) {
//                        var undoEraserCtx = undoEraserBuffer.getContext("2d")
//                        undoEraserCtx.clearRect(0, 0, width, height)
//                        undoEraserCtx.drawImage(canvas, 0, 0)
//                        undoEraserBuffer.requestPaint()
                    } else {
                        brushEngine.setTouch(true, canvas)
                        brushEngine.paint(Qt.point(mouse.x, mouse.y), 1)
                    }
                }
            }

            onReleased: {
                brushEngine.setTouch(false)
                if (isPan) {
                    coreLib.setCursorShape("OpenHand", 0)
                } else if (isPick) {
                    coreLib.setCursorShape("Paint", brushSettings.size * zoom)
                } else {
                }
            }

            onPositionChanged: {
                if (pressed) {
                    if (isPick) {
                        Utils.pickColor(Qt.point(mouseX, mouseY))
                    } else if (!isPan) {
                        brushEngine.paint(Qt.point(mouse.x, mouse.y), 1)
                    }
                } else if (isPan) {
                    content.x += (mouseX - grabPoint.x)
                    content.y += (mouseY - grabPoint.y)
                }
            }
        }
    }
}
