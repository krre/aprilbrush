import QtQuick 2.0
import "components"
import "utils.js" as Utils

Rectangle {
    //property int countPage: 1
    //property alias pagesView: pagesView
    property int currentPage: pagesView.currentIndex

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
                    var maxNumPage = 0;
                    for (var page = 0; page < pagesModel.count; page++)
                        if (pagesModel.get(page).hash > maxNumPage) maxNumPage = pagesModel.get(page).hash
                    maxNumPage++
                    var numNextPage = Utils.zeroFill(maxNumPage, 3)
                    pagesModel.append({name: "Page-" + numNextPage, hash: maxNumPage, activeLayer: 0, layerSet: [
                                              {name: "Layer-002", hash: 002, colorImage: "transparent", enable: true },
                                              {name: "Layer-001", hash: 001, colorImage: "white", enable: true } ]})
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

            Rectangle {
                id: pageContaner
                width: 100
                height: pagesView.height
                color: (index == pagesView.currentIndex) ? "transparent" : "lightgray"
                border.width: 1
                border.color: "gray"
                radius: 5
                antialiasing: true

                Text {
                    text: name
                    anchors.left: parent.left
                    anchors.leftMargin: 10
                    anchors.verticalCenter: parent.verticalCenter
                }

                MouseArea {
                    anchors.fill: parent
                    onClicked: {
                        pagesView.currentIndex = index
                        var hashPageLayer = pagesModel.get(currentPage).hash * 1000 + layersModel.get(currentLayer).hash
                        brush.setLayer(hashPageLayer)
                    }
                }
                CloseButton {
                    anchors.verticalCenter: parent.verticalCenter
                    anchors.right: parent.right
                    onClicked: {
                        console.log("index after " + index)
                        pagesModel.remove(index)
                        console.log("index after " + index)
                    }
                }
            }
        }

        Component {
            id: pageSelected
            Rectangle {
                width: 100
                height: pagesView.height
                border.width: 1
                border.color: "gray"
                radius: 5
                antialiasing: true
                color: "white"
            }
        }
    }
}
