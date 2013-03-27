import QtQuick 2.0
import QtGraphicalEffects 1.0
import "components"
import "utils.js" as Utils

Item {
    property alias pagesView: pagesView
    //property alias currentPage: pagesView.currentItem

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
                    onClicked: {
                        // Calculate next number page
                        var maxNumPage = 0;
                        for (var page = 0; page < pagesModel.count; page++) {
                            var numPage = parseInt(pagesModel.get(page).name.substring(6), 10)
                            if (numPage > maxNumPage) maxNumPage = numPage
                        }
                        maxNumPage++
                        var numNextPage = Utils.zeroFill(maxNumPage, 3)

                        pagesModel.append({name: "Page-" + numNextPage,
                                              layerSet: [
                                                  { name: "Layer-002", colorImage: "transparent", enable: true },
                                                  { name: "Layer-001", colorImage: "white", enable: true } ],
                                              undoSet: []
                                          })
                        // Placing a item on last position
                        pagesView.currentIndex = pagesModel.count - 1
                    }
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
                    onClicked: { pagesView.currentIndex = index; console.log(canvasArea.oraPath) }
                    onClosed: pagesModel.remove(index)

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

