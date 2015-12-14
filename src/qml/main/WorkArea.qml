import QtQuick 2.5
import QtQuick.Controls 1.4
import QtQuick.Layouts 1.1
import AprilBrush 1.0
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
    property string fileName: oraPath ? coreLib.pathToFileName(oraPath) : "Unnamed"
    property bool isDirty: false
    property string canvasMode: Enums.CanvasFree

    property real zoom: 1.0
    property int mirror: 1
    property real rotation: 0

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
        forceActiveFocus()
    }

    function resetTransform() {
        zoom = 1
        mirror = 1
        rotation = 0
        content.x = 0
        content.y = 0
//        content.x = (width - content.width) / 2
//        content.y = (height - content.height) / 2
    }

    function zoomIn() {
        if (zoom < 30) zoom *= 1.5
    }

    function zoomOut() {
        if (zoom > 0.01) zoom /= 1.5
    }

    ListModel { id: layerModel }

    ListModel { id: undoModel }

    Rectangle {
        id: content
        width: imageSize.width
        height: imageSize.height

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
                size: mainRoot.imageSize
                antialiasing: false
                z: 1000 - index
                visible: isVisible
                enabled: !isLock
                smooth: false

                Component.onCompleted: {
                    layerModel.set(index, { "canvasItem": this })
                }
            }

            onCountChanged: {
                mouseArea.enabled = count > 0
            }
        }

        Connections {
            target: TabletEventFilter
            onAction: {
                if (!canvasView.count) return

                var x = event.globalX - mainRoot.x
                var y = event.globalY - mainRoot.y
                var pos = canvasItem.itemPos(Qt.point(x, y))
                var pressure = event.pressure
                if (event.press === true) {
                    root.forceActiveFocus()
                    mouseArea.enabled = false
                    BrushEngine.setCanvasItem(canvasItem)
                    BrushEngine.isTouch = true
                    BrushEngine.paint(pos, pressure)
                } else if (event.release === true) {
                    mouseArea.enabled = true
                    BrushEngine.isTouch = true
                } else if (BrushEngine.isTouch) {
                    BrushEngine.paint(pos, pressure)
                }
            }
        }

        MouseArea {
            id: mouseArea
            anchors.fill: parent
            hoverEnabled: true
            drag.target: canvasMode === Enums.CanvasPan ? content : null
            drag.threshold: 1

            onPressed: {
                if (canvasMode === Enums.CanvasFree) {
                    canvasView.forceActiveFocus()
                    BrushEngine.isTouch = true
                    BrushEngine.setCanvasItem(canvasItem)
                    BrushEngine.paint(Qt.point(mouse.x, mouse.y))
                    canvasMode = Enums.CanvasPaint
                } else {
                    // pick color
                }
            }

            onPositionChanged: {
                if (pressed) {
                    if (canvasMode === Enums.CanvasPaint) {
                        BrushEngine.paint(Qt.point(mouse.x, mouse.y))
                    } else if (canvasMode === Enums.CanvasPick){
                        // pick color
                    }
                }
            }

            onReleased: {
                BrushEngine.isTouch = false
                if (canvasMode === Enums.CanvasPaint) {
                    canvasMode = Enums.CanvasFree
                }
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
        }

//        Label {
//            font.pointSize: 15
//            font.family: "FontAwesome"
//            text: FontAwesome.Icon.Plus
//        }
    }
}
