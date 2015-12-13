import QtQuick 2.5
import QtQuick.Controls 1.4
import QtQuick.Layouts 1.1
import AprilBrush 1.0
import "../../3rdparty/font-awesome/fontawesome.js" as FontAwesome

Item {
    id: root
    property bool isCurrentTab: mainRoot.currentTab === root
    property alias canvasItem: canvasItem
    property int currentLayerIndex: -1
    property int currentUndoIndex: -1
    property alias layerModel: layerModel
    property alias undoModel: undoModel
    property var commandArray: [] // array for saving undo/redo command (they don't work from ListModel)
    property int prevUndoIndex: -1
    property string oraPath
    property bool isDirty: false

    ListModel { id: layerModel }

    ListModel { id: undoModel }

    Rectangle {
        anchors.fill: parent

        CanvasItem {
            id: canvasItem
            anchors.fill: parent
            size: mainRoot.imageSize
            antialiasing: false

            Connections {
                property bool isTouch: false
                target: TabletEventFilter
                onAction: {
                    var x = event.globalX - mainRoot.x
                    var y = event.globalY - mainRoot.y
                    var pos = canvasItem.itemPos(Qt.point(x, y))
                    var pressure = event.pressure
                    if (event.press === true) {
                        mouseArea.enabled = false
                        isTouch = true
//                        brushEngine.setTouch(true)
                        BrushEngine.paint(pos.x, pos.y, canvasItem, pressure)
                    } else if (event.release === true) {
                        mouseArea.enabled = true
                        isTouch = false
//                        brushEngine.setTouch(false)
                    } else if (isTouch) {
                        BrushEngine.paint(pos.x, pos.y, canvasItem, pressure)
                    }
                }
            }

            MouseArea {
                id: mouseArea
                anchors.fill: parent

                onPressed: BrushEngine.paint(mouse.x, mouse.y, canvasItem)

                onPositionChanged: {
                    if (pressed) {
                        BrushEngine.paint(mouse.x, mouse.y, canvasItem)
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
