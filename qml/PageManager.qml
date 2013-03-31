import QtQuick 2.0
import QtGraphicalEffects 1.0
import "components"
import "utils.js" as Utils

Item {
    property alias pagesView: pagesView

    width: 600
    height: 40

    Rectangle {
        id: rect
        color: "#eeeeee"
        border.color: "gray"
        radius: 7
        antialiasing: true
        anchors.fill: parent

        Row {
            anchors.fill: parent
            // Button for adding page
            Item {
                id: addPageArea
                width: 30
                height: parent.height
                Text {
                    text: "+"
                    font.bold: true
                    font.pixelSize: 15
                    anchors.centerIn: parent
                }
                MouseArea {
                    anchors.fill: parent
                    onClicked: Utils.addPage()
                }
            }

            ListView {
                id: pagesView
                model: pagesModel
                delegate: pagesDelegate
                highlight: pageSelected
                highlightMoveDuration: 1

                height: parent.height - 8
                width: parent.width - addPageArea.width - 10
                anchors.verticalCenter: parent.verticalCenter
                orientation: ListView.Horizontal
                spacing: 5
                clip: true                
                onCurrentIndexChanged: {
                    if (currentIndex >= 0) {
                        var layerIndex = pagesView.currentItem.layerManager.currentLayerIndex
                        if (layerIndex >= 0)
                            currentLayerId = pagesModel.get(currentIndex).layerModel.get(layerIndex).layerId
                    }
                }
            }

            Component {               
                id: pagesDelegate
                ListItem {
                    property alias canvasArea: canvasArea
                    property alias undoManager: undoManager
                    property alias layerManager: layerManager
                    width: 100
                    height: pagesView.height
                    color: ListView.isCurrentItem ? "transparent" : "lightgray"
                    text: name
                    onClicked: { pagesView.currentIndex = index }
                    onClosed: Utils.deletePage(index)

                    CanvasArea {
                        id: canvasArea
                    }

                    LayerManager {
                        id: layerManager
                    }

                    UndoManager {
                        id: undoManager
                    }
                }
            }

            Component {
                id: pageSelected
                ListItemComponent {
                    width: 100
                    height: pagesView.height
                }
            }
        }
    }

    Shadow {
        surface: rect
    }
}
