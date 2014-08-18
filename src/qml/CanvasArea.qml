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
import QtQuick.Controls 1.2
import "components"
import "undo.js" as Undo

ScrollView {
    property alias layerModel: layerModel
    property alias undoModel: undoModel
    property Canvas canvas: layerCanvasView.currentItem
    property string oraPath

    property real zoom: 1.0
    property bool isPan: false
    property point pan: Qt.point(0, 0)
    property int mirror: 1
    property real rotation: 0

    Keys.onPressed: {
        if (event.key === Qt.Key_Space && !event.isAutoRepeat) { isPan = true }
//            case Qt.Key_F: undoManager.add(new Undo.fillColor()); break
//            case Qt.Key_Z: undoManager.undoView.decrementCurrentIndex(); break
//            case Qt.Key_X: undoManager.undoView.incrementCurrentIndex(); break
//        if (event.modifiers & Qt.ControlModifier)
//            ctrlMode = true
    }

    Keys.onReleased: {
//        if (Qt.ControlModifier)
//            ctrlMode = false
        if (event.key === Qt.Key_Space && !event.isAutoRepeat) { isPan = false }
    }

    Component.onCompleted: forceActiveFocus()

    function resetTransform() {
          zoom = 1
          pan = Qt.point(0, 0)
          mirror = 1
          rotation = 0
    }

    Item {
        x: pan.x
        y: pan.y
        width: imageSize.width
        height: imageSize.height

        ListModel { id: layerModel }
        ListModel { id: undoModel }

        transform: [
            Scale { origin.x: width / 2; origin.y: height / 2; xScale: zoom * mirror; yScale: zoom },
            Rotation { origin.x: width / 2; origin.y: height / 2; angle: rotation }
        ]

        CheckerBoard {
            anchors.fill: parent
            cellSide: 30
        }

        ListView {
            id: layerCanvasView
            anchors.fill: parent
            model: layerModel
            spacing: -width
            orientation: ListView.Horizontal
            currentIndex: layerManager.tableView.currentRow
            interactive: false
            delegate: Canvas {
                z: 1000 - index
                width: ListView.view.width
                height: ListView.view.height
                antialiasing: true
                smooth: false
                visible: layerVisible
                onAvailableChanged: clear(true)

                Component.onCompleted: layerModel.set(index, { "canvas": this })

                function clear(init) {
                    var ctx = getContext("2d")
                    ctx.save()
                    if (color === "transparent") {
                        ctx.clearRect(0, 0, width, height)
                    } else {
                        ctx.fillStyle = color
                        ctx.fillRect(0, 0, width, height)
                    }
                    ctx.restore()
                    requestPaint()
                    if (!init) {
                        undoManager.add(new Undo.clear())
                    }
                }
            }

            MouseArea {
                property real deltaDab: Math.max(brushSettings.spacing / 100 * brushSettings.diameter, 1)
                property var points: []
                property bool linearMode: false
                property point lastDrawPoint
                property point grabPoint
                anchors.fill: parent
                enabled: currentLayerIndex >= 0 && typeof layerModel.get(currentLayerIndex) !== "undefined" && !layerModel.get(currentLayerIndex).blocked

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
                    if (isPan) {
                        grabPoint = point
                    } else {
                        lastDrawPoint = point
                        drawDab(point)
                        points = []
                        points.push(point)
                    }
                }

                onReleased: {
                    undoManager.add(new Undo.paint())
                }

                onPositionChanged: {
                    if (isPan) {
                        pan.x += (mouseX - grabPoint.x) * zoom * mirror
                        pan.y += (mouseY - grabPoint.y) * zoom
                    } else {
                        var currentPoint = Qt.point(mouseX, mouseY)
                        var startPoint = lastDrawPoint
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
                                    drawDab(point)
                                    diff = undefined
                                    betweenPoint = point
                                    t += deltaT
                                } else {
                                    t -= diff / deltaDab * deltaT
                                }
                            }
                            points.push(currentPoint)
                            lastDrawPoint = betweenPoint
                        }
                    }
                }

                function drawDab(point) {
                    var dabCanvas = brushSettings.dab
                    var ctx = canvas.getContext("2d")
                    ctx.save()
                    ctx.globalCompositeOperation = isEraser ? "destination-out" : "source-over"
                    var x = point.x - brushSettings.dab.width / 2
                    var y = point.y - brushSettings.dab.height / 2
                    ctx.drawImage(dabCanvas, x, y)
                    ctx.restore()
                    canvas.markDirty(x, y, brushSettings.dab.width, brushSettings.dab.height)
                }
            }
        }
    }
}
