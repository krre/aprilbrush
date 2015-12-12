import QtQuick 2.5
import QtQuick.Controls 1.4
import QtQuick.Layouts 1.1
import AprilBrush 1.0
import "../../3rdparty/font-awesome/fontawesome.js" as FontAwesome

Item {
    id: root
    property bool isCurrentTab: mainRoot.currentTab === root
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

            MouseArea {
                anchors.fill: parent

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
