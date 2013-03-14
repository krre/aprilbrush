import QtQuick 2.0
import "components"
import "utils.js" as Utils

Rectangle {
    property int currentPage: pagesView.currentIndex
    property int currentLayer: layerManager.currentLayer

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
                    if (pagesModel.count > 0)
                        pagesModel.set(currentPage, { activeLayer: currentLayer })
                    var maxNumPage = 0;
                    for (var page = 0; page < pagesModel.count; page++)
                        if (pagesModel.get(page).hashPage > maxNumPage) maxNumPage = pagesModel.get(page).hashPage
                    maxNumPage++
                    var numNextPage = Utils.zeroFill(maxNumPage, 3)
                    pagesModel.append({name: "Page-" + numNextPage, hashPage: maxNumPage, activeLayer: 0, layerSet: [
                                              {name: "Layer-002", hashLayer: 002, colorImage: "transparent", enable: true },
                                              {name: "Layer-001", hashLayer: 001, colorImage: "white", enable: true } ]})
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
                        pagesModel.set(currentPage, {activeLayer: currentLayer})
                        pagesView.currentIndex = index
                        layerManager.layerView.currentIndex = pagesModel.get(index).activeLayer
                    }
                }
                CloseButton {
                    anchors.verticalCenter: parent.verticalCenter
                    anchors.right: parent.right
                    onClicked: {
                        if (index > 0)
                            layerManager.layerView.currentIndex = pagesModel.get(index - 1).activeLayer
                        var hashArray = []
                        for (var i = 0; i < layersModel.count; i++) {
                            hashArray.push(hashPage * 1000 + layersModel.get(i).hashLayer)
                        }

                        pagesModel.remove(index)
                        var hashPageLayer
                        for (var i = hashArray.length - 1; i >= 0; i--) {
                            brush.deleteLayer(hashArray[i])
                        }
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
