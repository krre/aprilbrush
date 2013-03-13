import QtQuick 2.0
import "components"
import "utils.js" as Utils

Rectangle {
    property int countPage: 1
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
                    var numNextPage = Utils.zeroFill(++countPage, 2)
                    pagesModel.append({name: "Page-" + numNextPage, activeLayer: 1, layerSet: [
                                              {name: "Layer-01", number: 2, colorImage: "transparent", enable: true },
                                              {name: "Background", number: 1, colorImage: "white", enable: true } ]})
                    pagesView.currentIndex = pagesModel.count - 1
                }
            }
        }

        ListView {
            id: pagesView
            model: pagesModel
            delegate: pagesDelegate
            highlight: pageSelected

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
                color: "lightgray"
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
                        //console.log(layersModel.get(index).active)
                        pagesView.currentIndex = index
                        //layerManager.lView.currentIndex = layersModel.get(layerManager.lView.currentIndex).active
                        //layersModel.get(layerManager.lView.currentIndex) = layersModel.get(index).active
                        //brush.setLayer(layersModel.get(layerManager.lView.currentIndex).number)
                    }
                }
                CloseButton {
                    anchors.verticalCenter: parent.verticalCenter
                    anchors.right: parent.right
                    onClicked: {
                        if (pagesModel.count > 0) pagesModel.remove(index)
                    }
                }
            }
        }

        Component {
            id: pageSelected
            Rectangle {
                width: 100
                height: pagesView.height
                color: "red"
            }
        }
    }
}
