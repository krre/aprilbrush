import QtQuick 2.6
import QtQuick.Controls 1.5
import QtQuick.Layouts 1.3
import AprilBrush 1.0
import "../../js/utils.js" as Utils
import "../../js/undo.js" as Undo
import "../../js/enums.js" as Enums
import "../../3rdparty/font-awesome/fontawesome.js" as FontAwesome

Item {
    id: root
    property bool isCurrentTab: mainRoot.currentTab === root
    property alias canvasItem: canvasView.currentItem
    property int currentLayerIndex: -1
    property int currentUndoIndex: -1
    property alias layerModel: layerModel
    property alias undoModel: undoModel
    property var commandArray: [] // array for saving undo/redo command (they don't work from ListModel)
    property int prevUndoIndex: -1
    property string oraPath
    property string fileName: oraPath ? Core.pathToFileName(oraPath) : "Unnamed"
    property bool isDirty: false
    property string canvasMode: Enums.CanvasFree
    property size canvasSize
    property alias backgroundColor: content.color

    property real zoom: 1.0
    property int mirror: 1
    property real rotation: 0
    visible: false

    onCanvasModeChanged: {
        Core.setCursorShape(canvasMode === Enums.CanvasFree && mouseArea.containsMouse || canvasMode === Enums.CanvasPaint ?
                                   Enums.CanvasPaint : canvasMode, brushSettings.size * zoom)
    }

    onZoomChanged: {
        if (mouseArea.containsMouse) {
            Core.setCursorShape(Enums.CanvasPaint, brushSettings.size * zoom)
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

    Component.onCompleted: {
        forceActiveFocus()
        timer.start()
    }

    function resetTransform() {
        zoom = 1
        mirror = 1
        rotation = 0
        content.x = 0
        content.y = 0
        content.x = (width - canvasSize.width) / 2
        content.y = (height - canvasSize.height) / 2
    }

    function zoomIn() {
        if (zoom < 30) zoom *= 1.5
    }

    function zoomOut() {
        if (zoom > 0.01) zoom /= 1.5
    }

    Timer {
        id: timer
        interval: 100
        onTriggered: {
            resetTransform()
            root.visible = true
        }
    }

    ListModel { id: layerModel }

    ListModel { id: undoModel }

    Rectangle {
        id: content
        width: canvasSize.width
        height: canvasSize.height

        transform: [
            Scale { origin.x: content.width / 2; origin.y: content.height / 2; xScale: zoom * mirror; yScale: zoom },
            Rotation { origin.x: content.width / 2; origin.y: content.height / 2; angle: rotation }
        ]

        ListView {
            id: canvasView
            anchors.fill: parent
            model: layerModel
            spacing: -width
            orientation: ListView.Horizontal
            currentIndex: layerManager.currentIndex
            interactive: false
            delegate: CanvasItem {
                width: ListView.view.width
                height: ListView.view.height
                size: canvasSize
                antialiasing: false
                z: 1000 - index
                visible: isVisible
                enabled: !isLock
                smooth: false

                Component.onCompleted: {
                    layerModel.set(index, { "canvasItem": this })
                    var image = layerModel.get(index).image
                    if (image) { // load PNG from ora file or undo buffer
                        setImage(Core.base64ToByteArray(image))
                        image = undefined
                    }
                }
            }
        }

        CanvasItem {
            id: canvasBuffer
            parent: canvasItem
            anchors.fill: parent
            size: Qt.size(content.width, content.height)
            antialiasing: false
            smooth: false
            opacity: brushSettings.opaque / 100
        }

//        Label {
//            font.pointSize: 15
//            font.family: "FontAwesome"
//            text: FontAwesome.Icon.Plus
//        }
    }

    MouseArea {
        id: mouseArea
        anchors.fill: parent
        drag.target: canvasMode === Enums.CanvasPan ? content : null
        drag.threshold: 1
        hoverEnabled: true

        onContainsMouseChanged: {
            Core.setCursorShape(containsMouse && canvasMode === Enums.CanvasFree ? Enums.CanvasPaint : canvasMode, brushSettings.size * zoom)
        }

        onPressed: {
            if (!(canvasView.count && canvasItem.enabled)) return
            var pos = Qt.point(mouse.x - content.x, mouse.y - content.y)
            if (canvasMode === Enums.CanvasFree) {
                canvasView.forceActiveFocus()
                BrushEngine.setCanvasItem(canvasItem)
                BrushEngine.setCanvasBuffer(canvasBuffer)
                BrushEngine.isTouch = true
                canvasMode = Enums.CanvasPaint
                BrushEngine.paint(pos)
            } else {
                Utils.pickColor(pos)
            }
        }

        onPositionChanged: {
            if (!(canvasView.count && canvasItem.enabled)) return

            if (pressed) {
                var pos = Qt.point(mouse.x - content.x, mouse.y - content.y)
                if (canvasMode === Enums.CanvasPaint) {
                    BrushEngine.paint(pos)
                } else if (canvasMode === Enums.CanvasPick){
                    Utils.pickColor(pos)
                }
            }
        }

        onReleased: {
            BrushEngine.isTouch = false
            if (canvasMode === Enums.CanvasPaint) {
                undoManager.add(Undo.paint())
                canvasMode = Enums.CanvasFree
            }
        }

        onWheel: {
            if (wheel.angleDelta.y > 0) {
                zoomIn()
            } else {
                zoomOut()
            }
        }
    }

    Connections {
        target: TabletEventFilter
        onAction: {
            if (!(canvasView.count && canvasItem.enabled)) return

            var x = event.globalX - mainRoot.x
            var y = event.globalY - mainRoot.y
            var pos = canvasItem.itemPos(Qt.point(x, y))
            var pressure = event.pressure
            if (event.press === true) {
                root.forceActiveFocus()
                BrushEngine.setCanvasItem(canvasItem)
                BrushEngine.setCanvasBuffer(canvasBuffer)
                BrushEngine.isTouch = true
                canvasMode = Enums.CanvasPaint
                BrushEngine.paint(pos, pressure)
            } else if (event.release === true) {
                BrushEngine.isTouch = true
                undoManager.add(Undo.paint())
            } else if (BrushEngine.isTouch) {
                BrushEngine.paint(pos, pressure)
            }
        }
    }
}
