import QtQuick 2.4
import QtQuick.Controls 1.3
import ABLib 1.0
import "components"
import "undo.js" as Undo
import "utils.js" as Utils
import "enums.js" as Enums

Item {
    id: root
    property alias canvas: canvasView.currentItem
    property alias canvasView: canvasView
    property color bgColor: "white"
    property string canvasMode: Enums.CanvasFree

    property real zoom: 1.0
    property int mirror: 1
    property real rotation: 0

    onCanvasModeChanged: {
        coreLib.setCursorShape(canvasMode === Enums.CanvasFree && mouseArea.containsMouse || canvas === Enums.CanvasPaint ?
                                   "paint" : canvasMode, brushSettings.size * zoom)
    }
    onBgColorChanged: layerModel.get(layerModel.count - 1).canvas.clear(bgColor)
    onZoomChanged: {
        if (mouseArea.containsMouse) {
            coreLib.setCursorShape("paint", brushSettings.size * zoom)
        }
    }

    Keys.onPressed: {
        if (!event.isAutoRepeat) {
            if (event.key === Qt.Key_Space) {
                canvasMode = Enums.CanvasPan
            } else if (event.modifiers & Qt.AltModifier) {
                canvasMode = Enums.CanvasPick
            }
        }
    }

    Keys.onReleased: {
        if (!event.isAutoRepeat) {
            canvasMode = Enums.CanvasFree
        }
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
            signal created(var index, var canvas)
            delegate: Canvas {
                width: ListView.view.width
                height: ListView.view.height
                z: 1000 - index
                visible: isVisible
                enabled: !isLock
                smooth: false

                signal ready

                onAvailableChanged: {
                    clear()
                    ready()
                }

                Component.onCompleted: {
                    layerModel.set(index, { "canvas": this })
                    canvasView.created(index, this)
                }

                function clear() {
                    var ctx = getContext("2d")
                    ctx.clearRect(0, 0, width, height)
                    requestPaint()
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
            hoverEnabled: true
            drag.target: canvasMode === Enums.CanvasPan ? content : null
            drag.threshold: 1

            onContainsMouseChanged: {
                coreLib.setCursorShape(containsMouse && canvasMode === Enums.CanvasFree ? "paint" : canvasMode, brushSettings.size * zoom)
            }

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
                if (canvasMode === Enums.CanvasFree) {
                    brushEngine.setTouch(true, canvas)
                    brushEngine.paint(Qt.point(mouse.x, mouse.y), 1)
                    canvasMode = Enums.CanvasPaint
                } else if (canvasMode === Enums.CanvasPick) {
                    Utils.pickColor(Qt.point(mouseX, mouseY))
                }
            }

            onReleased: {
                brushEngine.setTouch(false)
                if (canvasMode === Enums.CanvasPaint) {
                    canvasMode = Enums.CanvasFree
                }
            }

            onPositionChanged: {
                if (pressed) {
                    if (canvasMode === Enums.CanvasPaint) {
                        brushEngine.paint(Qt.point(mouse.x, mouse.y), 1)
                    } else if (canvasMode === Enums.CanvasPick){
                        Utils.pickColor(Qt.point(mouseX, mouseY))
                    }
                }
            }
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
        id: pickCanvas
        width: 1
        height: 1
        visible: false
    }
}

/*

ScrollView {
    property alias layerModel: layerModel
    property alias undoModel: undoModel
    property int prevUndoIndex: -1
    property var commandArray: [] // array for saving undo/redo command (they don't work from ListModel)
    property int layerNameIndexCounter: 1
    property int savedLayerIndex: 0
    property int savedUndoIndex: 0

    property alias canvas: canvasView.currentItem
    property alias canvasView: canvasView
    property string oraPath
    property bool isCtrlPressed: false
    property string cursorName: "Paint"
    property color bgColor: "white"

    Item {
        width: imageSize.width
        height: imageSize.height

        ListModel { id: layerModel }
        ListModel { id: undoModel }

        // temporary dirty hack for undo eraser brush
        Canvas {
            id: undoEraserBuffer
            anchors.fill: parent
            visible: false
            smooth: false
        }

        Canvas {
            id: buffer
            z: 1001
            anchors.fill: parent
            parent: canvasView.currentItem
            opacity: brushSettings.opacity / 100
            smooth: false

            MouseArea {

                anchors.fill: parent
                enabled: buffer.parent ? buffer.parent.enabled : false
                hoverEnabled: true

                onHoveredChanged: coreLib.setCursorShape(containsMouse ? cursorName : "Arrow", brushSettings.size * zoom)

                onPressed: {
                    var point = Qt.point(mouseX, mouseY)
                    if (isPan) {
                        grabPoint = point
                        cursorName = "CloseHand"
                        coreLib.setCursorShape(cursorName, 0)
                    } else if (isCtrlPressed) {
                        Utils.pickColor(point)
                    } else {
                        if (isEraser) {
                            var undoEraserCtx = undoEraserBuffer.getContext("2d")
                            undoEraserCtx.clearRect(0, 0, width, height)
                            undoEraserCtx.drawImage(canvas, 0, 0)
                            undoEraserBuffer.requestPaint()
                        }

//                        print(mouseX, mouseX, mainRoot.pressure)
                        startPos = Qt.point(point.x, point.y)
                        finalPos = Qt.point(point.x, point.y)
                        lastDrawPoint = point
                        drawDab(point)
                        points = []
                        points.push(point)
                    }
                }

                onReleased: {
                    mainRoot.pressure = 1
                    if (!isCtrlPressed && !isPan) {
                        startPos.x -= dab.width
                        startPos.y -= dab.width
                        finalPos.x += dab.width
                        finalPos.y += dab.width

                        var bufferCtx = parent.getContext("2d")
                        var canvasCtx = canvas.getContext("2d")
                        if (!isEraser) {
                            var undoArea = canvasCtx.getImageData(startPos.x, startPos.y, finalPos.x - startPos.x, finalPos.y - startPos.y)
                            var redoArea = bufferCtx.getImageData(startPos.x, startPos.y, finalPos.x - startPos.x, finalPos.y - startPos.y)
                        } else {
                            undoArea = undoEraserBuffer.getContext("2d").getImageData(startPos.x, startPos.y, finalPos.x - startPos.x, finalPos.y - startPos.y)
                            redoArea = canvasCtx.getImageData(startPos.x, startPos.y, finalPos.x - startPos.x, finalPos.y - startPos.y)
                        }
                        undoManager.add(Undo.paint(startPos, undoArea, redoArea, brushSettings.opacity / 100, isEraser))
                        bufferCtx.clearRect(0, 0, width, height)
                        parent.requestPaint()
                    } else if (isPan) {
                        cursorName = "OpenHand"
                        coreLib.setCursorShape(cursorName, 0)
                    }
                }

                onPositionChanged: {
                    if (!pressed || isPan) { return; }
                    if (isCtrlPressed) {
                        Utils.pickColor(Qt.point(mouseX, mouseY))
                    } else {
                        var currentPoint = Qt.point(mouseX, mouseY)
//                        print(mouseX, mouseX, mainRoot.pressure)
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

                }
            }
        }

}



*/
