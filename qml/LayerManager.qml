import QtQuick 2.0
import "components"
import "utils.js" as Utils

Window {
    title: "Layers"
    property variant layersModel: layers

    Column {
        width: parent.width
        spacing: 5

        ListView {
            id: layersView
            model: layersModel
            delegate: layerDelegate
            highlight: layerSelected

            width: parent.width
            height: 120

            orientation: ListView.Vertical
            clip: true
            spacing: 4
            focus: true
        }

        Component {
            id: layerDelegate
            Rectangle {
                width: parent.width
                height: 20
                color: "lightgray"
                border.width: 1
                border.color: "gray"
                radius: 5
                antialiasing: true
                Text {
                    text: name
                    anchors.verticalCenter: parent.verticalCenter
                    anchors.left: parent.left
                    anchors.leftMargin: 10
                }
                MouseArea {
                    anchors.fill: parent
                    onClicked: layersView.currentIndex = index
                }
            }
        }

        Component {
            id: layerSelected
            Rectangle {
                width: layersView.width
                height: 20
                color: "red"
            }
        }

        ListModel {
            id: layers
            ListElement { name: "Layer-01" }
            ListElement { name: "Background" }
        }

        Row {
            width: parent.width
            height: 20
            spacing: 4

            Rectangle {
                width: parent.width / 4 - 4
                height: parent.height
                color: "lightgray"
                radius: 5
                antialiasing: true
                Text {
                    text: qsTr("New")
                    anchors.centerIn: parent
                }
                MouseArea {
                    anchors.fill: parent
                    onClicked: {
                        var numNextLayer = Utils.zeroFill(layersModel.count, 2)
                        if (layersView.currentIndex < 0)
                            layersView.currentIndex = 0
                        layersModel.insert(layersView.currentIndex, { name: "Layer-" + numNextLayer, image: "01.png", enable: true })
                        layersView.currentIndex--
                    }
                }
            }

            Rectangle {
                width: parent.width / 4 - 4
                height: parent.height
                color: "lightgray"
                radius: 5
                antialiasing: true
                Text {
                    text: qsTr("Up")
                    anchors.centerIn: parent
                }
                MouseArea {
                    anchors.fill: parent
                    onClicked: {
                        if (layersView.currentIndex > 0)
                            layersModel.move(layersView.currentIndex, layersView.currentIndex - 1, 1)                        
                    }
                }
            }

            Rectangle {
                width: parent.width / 4 - 4
                height: parent.height
                color: "lightgray"
                radius: 5
                antialiasing: true
                Text {
                    text: qsTr("Down")
                    anchors.centerIn: parent
                }
                MouseArea {
                    anchors.fill: parent
                    onClicked: {
                        if (layersView.currentIndex < layersView.count - 1)
                            layersModel.move(layersView.currentIndex, layersView.currentIndex + 1, 1)
                    }
                }
            }

            Rectangle {
                width: parent.width / 4 - 4
                height: parent.height
                color: "lightgray"
                radius: 5
                antialiasing: true
                Text {
                    text: qsTr("Delete")
                    anchors.centerIn: parent
                }
                MouseArea {
                    anchors.fill: parent
                    onClicked: {
                        if (layersModel.count > 0)
                            layersModel.remove(layersView.currentIndex)
                    }
                }
            }
        }
    }
}
