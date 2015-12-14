import QtQuick 2.5
import QtQuick.Controls 1.4
import QtQuick.Layouts 1.1
import AprilBrush 1.0
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
    property bool isDirty: false

    Component.onCompleted: canvasView.forceActiveFocus()

    ListModel { id: layerModel }

    ListModel { id: undoModel }

    Rectangle {
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
            }
        }

        Connections {
            target: TabletEventFilter
            onAction: {
                var x = event.globalX - mainRoot.x
                var y = event.globalY - mainRoot.y
                var pos = canvasItem.itemPos(Qt.point(x, y))
                var pressure = event.pressure
                if (event.press === true) {
                    canvasView.forceActiveFocus()
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

            onPressed: {
                canvasView.forceActiveFocus()
                BrushEngine.isTouch = true
                BrushEngine.setCanvasItem(canvasItem)
                BrushEngine.paint(Qt.point(mouse.x, mouse.y))
            }

            onPositionChanged: {
                if (pressed) {
                    BrushEngine.paint(Qt.point(mouse.x, mouse.y))
                }
            }

            onReleased: BrushEngine.isTouch = false
        }

//        Label {
//            font.pointSize: 15
//            font.family: "FontAwesome"
//            text: FontAwesome.Icon.Plus
//        }
    }
}
