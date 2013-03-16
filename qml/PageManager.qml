import QtQuick 2.0
import "components"
import "utils.js" as Utils

Rectangle {
    property alias pagesView: pagesView

    width: 600
    height: 40
    color: "#eeeeee"
    border.color: "gray"
    radius: 7
    antialiasing: true

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
                        var numPage = parseInt(pagesModel.get(page).name.substring(6))
                        if (numPage > maxNumPage) maxNumPage = numPage
                    }
                    maxNumPage++
                    var numNextPage = Utils.zeroFill(maxNumPage, 3)

                    pagesModel.append({name: "Page-" + numNextPage,
                                          layerSet: [
                                              { name: "Layer-002", colorImage: "transparent", enable: true },
                                              { name: "Layer-001", colorImage: "white", enable: true } ],
                                          undoSet: [
                                              { name: "Start" },
                                              { name: "Paint" } ]
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
                width: 100
                height: pagesView.height
                color: (index == pagesView.currentIndex) ? "transparent" : "lightgray"
                text: name
                onClicked: pagesView.currentIndex = index
                onClosed: pagesModel.remove(index)

                CanvasArea {
                    id: canvasArea
                }

                LayerManager {
                    id: layerManager
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
