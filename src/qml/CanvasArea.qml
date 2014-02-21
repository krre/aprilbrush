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

Canvas {
    id: canvas
    property point lastDrawPoint
    width: imageSize.width
    height: imageSize.height
//        antialiasing: true
    smooth: false
    visible: ListView.isCurrentItem

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
        canvas.requestPaint()
        pageManager.pageView.currentItem.paintThumbnail()
    }

    MouseArea {
        property real deltaDab: Math.max(canvas.spacing * canvas.diameter, 1)
        property var points: []
        property bool linearMode: false
        anchors.fill: parent
        propagateComposedEvents: true

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
        onReleased: {
            pageManager.pageView.currentItem.paintThumbnail()
            if (layerModel.count > 0) {
                layerManager.layerView.currentItem.thumbnail.paintThumbnail()
            }
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
        var dabCanvas = brushSettings.dab.getContext("2d").getImageData(0, 0, brushSettings.dab.width, brushSettings.dab.height)
        var ctx = canvas.getContext("2d")
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
        markDirty(point.x - brushSettings.dab.width / 2, point.y - brushSettings.dab.height / 2, brushSettings.dab.width, brushSettings.dab.height)
    }
}

/*
import QtQuick 2.1
import ABLib 1.0
import "components"
import "utils.js" as Utils
import "undo.js" as Undo

Item {
    id: root
    property alias pathView: pathView
    property real zoom: 1
    property bool panMode: false
    property point pan: Qt.point(0, 0)
    property int mirror: 1
    property real rotation: 0
    property bool saved: false
    property string oraPath
    property bool focusBind: true
    property string cursorName: "Paint"
    property bool ctrlMode: false

    width: imageSize.width
    height: imageSize.height

    Keys.onPressed: {
        switch (event.key) {
            case Qt.Key_Plus: zoom *= 1.5; break
            case Qt.Key_Minus: zoom /= 1.5; break
            case Qt.Key_0: zoom = 1; pan = Qt.point(0, 0); mirror = 1; rotation = 0; break
            case Qt.Key_Space: if (!event.isAutoRepeat) panMode = true; break
            case Qt.Key_M: mirror *= -1; break
            case Qt.Key_R: rotation += 90; break
        }

        if (event.modifiers & Qt.ControlModifier)
            ctrlMode = true
    }

    Keys.onReleased: {
        if (Qt.ControlModifier)
            ctrlMode = false
        if (event.key === Qt.Key_Space) { if (!event.isAutoRepeat) panMode = false }
    }

    CheckerBoard {
        id: checkerBoard
        width: imageSize.width
        height: imageSize.height
        anchors.centerIn: parent
        cellSide: 30
        transform: [
            Scale { origin.x: width / 2; origin.y: height / 2; xScale: zoom * mirror; yScale: zoom },
            Rotation { origin.x: width / 2; origin.y: height / 2; angle: rotation }
        ]
    }

    PathView {
        id: pathView
        anchors.centerIn: parent
        model: layerModel
        delegate: paintedItemDelegate

        highlightRangeMode: PathView.NoHighlightRange
        path: Path {
            PathAttribute { name: "z"; value: 9999.0 }
            PathLine { x: 0; y: 0 }
            PathAttribute { name: "z"; value: 0.0 }
        }
        currentIndex: layerManager.layerView.currentIndex
    }

    Component {
        id: paintedItemDelegate

        PaintedItem {
            id: paintedItem
            objectName: layerId
            width: root.width
            height: root.height
            imageProcessor: imgProcessor
            z: 1000 - index
            visible: enable

            MouseArea {
                property real zoomItem: zoom
                property bool panModeItem: panMode
                property point grabPoint

                anchors.fill: parent
                hoverEnabled: true
                onHoveredChanged: containsMouse ? paintedItem.setItemCursor(cursorName, brushSettings.size.value * zoom) : paintedItem.unSetItemCursor()
                onZoomItemChanged: containsMouse ? paintedItem.setItemCursor(cursorName, brushSettings.size.value * zoom) : paintedItem.unSetItemCursor()
                onPanModeItemChanged: if (panModeItem) {
                                          cursorName = "OpenHand";
                                          paintedItem.setItemCursor(cursorName, 0)
                                      }
                                      else {
                                          cursorName = "Paint";
                                          paintedItem.setItemCursor(cursorName, brushSettings.size.value * zoom)
                                      }
                onPressed:
                    if (panMode) {
                        cursorName = "ClosedHand"
                        paintedItem.setItemCursor(cursorName, 0)
                        grabPoint = Qt.point(mouseX, mouseY)
                    }
                    else {
                        if (ctrlMode)
                            colorPicker.color = Utils.pickColor(Qt.point(mouseX, mouseY))
                        else {
                            brushEngine.setTouch(Qt.point(mouseX, mouseY))
                            brushEngine.paintDab(Qt.point(mouseX, mouseY), pressure)
                        }
                    }
                onReleased:
                    if (panMode) {
                        cursorName = "OpenHand"
                        paintedItem.setItemCursor(cursorName, 0)
                    }
                    else
                        if (!ctrlMode)
                        {
                            brushEngine.setUnTouch();
                            undoManager.add(new Undo.paint())
                        }
                onPositionChanged:
                    if (pressed) {
                        if (panModeItem) {
                            pan.x += (mouseX - grabPoint.x) * zoom * mirror
                            pan.y += (mouseY - grabPoint.y) * zoom
                        }
                        else {
                            if (ctrlMode)
                                colorPicker.color = Utils.pickColor(Qt.point(mouseX, mouseY))
                            else {
                                brushEngine.paintDab(Qt.point(mouseX, mouseY), mainRoot.pressure)
//                                console.log(mainRoot.pressure)
                            }
                        }
                    }
            }
        }
    }
}
*/
