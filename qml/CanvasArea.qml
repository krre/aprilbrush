import QtQuick 2.5
import QtQuick.Controls 1.3
import AprilBrush 1.0
import "components"
import "../js/undo.js" as Undo
import "../js/utils.js" as Utils
import "../js/enums.js" as Enums

Item {
    id: root
    property alias canvas: canvasView.currentItem
    property alias canvasView: canvasView
    property alias exportCanvas: exportCanvas
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
                    brushEngine.setTouch(true)
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
                    brushEngine.setTouch(true)
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
                var ctx = getContext("2d")
                ctx.fillStyle = bgColor
                ctx.fillRect(0, 0, width, height)

                for (var i = layerModel.count - 1; i > -1; i--) {
                    var canvas = layerModel.get(i).canvas
                    var image = canvas.getContext("2d").getImageData(0, 0, width, height)
                    ctx.drawImage(canvas, 0, 0)
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
