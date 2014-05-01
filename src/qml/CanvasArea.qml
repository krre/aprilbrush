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

import QtQuick 2.2
import QtQuick.Controls 1.1
import "components"

ScrollView {
    Item {
//        property alias layerCanvasView: layerCanvasView
        width: imageSize.width
        height: imageSize.height

        CheckerBoard {
            anchors.fill: parent
            cellSide: 20
        }


        ListModel { id: layerModel }

      /*
        ListView {
            id: layerCanvasView
            anchors.fill: parent
            model: layerModel
            visible: parent.ListView.isCurrentItem
            spacing: -width
            orientation: ListView.Horizontal
            currentIndex: layerManager.layerView.currentIndex
            interactive: false
            delegate: Canvas {
                z: 1000 - index
                width: ListView.view.width
                height: ListView.view.height
            //        antialiasing: true
                smooth: false
                visible: visibled
                onAvailableChanged: clear()

                function clear() {
                    var ctx = getContext("2d")
                    ctx.save()
                    ctx.fillStyle = color
                    ctx.fillRect(0, 0, width, height)
                    ctx.restore();
                    requestPaint()
                    pageManager.pageView.currentItem.canvas.paintThumbnail()
                }
            }

            MouseArea {
                property real deltaDab: Math.max(brushSettings.spacing / 100 * brushSettings.diameter, 1)
                property var points: []
                property bool linearMode: false
                property point lastDrawPoint
                anchors.fill: parent

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
                    if (layerModel.get(currentLayerIndex).blocked) { return }

                    var point = Qt.point(mouseX, mouseY)
                    lastDrawPoint = point
                    drawDab(point)
                    points = []
                    points.push(point)
                }
                onReleased: {
                    if (layerModel.get(currentLayerIndex).blocked) { return }

                    pageManager.pageView.currentItem.canvas.paintThumbnail()
                    if (layerModel.count > 0) {
                        layerManager.layerView.currentItem.thumbnail.paintThumbnail()
                    }
                }

                onPositionChanged: {
                    if (layerModel.get(currentLayerIndex).blocked) { return }

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

                function drawDab(point) {
            //            console.log(point)
                    var dabCanvas = brushSettings.dab.getContext("2d").getImageData(0, 0, brushSettings.dab.width, brushSettings.dab.height)
                    var ctx = layerCanvasView.currentItem.getContext("2d")
                    ctx.save()
                    var x = point.x - brushSettings.dab.width / 2
                    var y = point.y - brushSettings.dab.height / 2
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
                    layerCanvasView.currentItem.markDirty(point.x - brushSettings.dab.width / 2, point.y - brushSettings.dab.height / 2, brushSettings.dab.width, brushSettings.dab.height)
                }
            }
        }
    */
    }
}
