import QtQuick 2.6
import QtQuick.Controls 1.5
import QtQuick.Layouts 1.3
import QtQuick.Controls.Styles 1.4
import "../components"
import "../../js/brush-lib.js" as BrushLib

Panel {
    property int currentBrush: 0
    id: root
    title: qsTr("Brush Library")
    objectName: "brushLibrary"

    Component.onCompleted: {
        loadBrushes()
    }

    function changeBrushSettings(row) {
        brushSettings.size = libraryModel.get(row).size
        brushSettings.opacity = libraryModel.get(row).opacity
        brushSettings.flow = libraryModel.get(row).flow
        brushSettings.spacing = libraryModel.get(row).spacing
        brushSettings.hardness = libraryModel.get(row).hardness
        brushSettings.roundness = libraryModel.get(row).roundness
        brushSettings.angle = libraryModel.get(row).angle
        brushSettings.jitter = libraryModel.get(row).jitter
        brushSettings.eraser = libraryModel.get(row).eraser
        currentBrush = row
    }

    function loadBrushes() {
        for(var i in BrushLib.defaultPack) {
            var brush = BrushLib.defaultPack[i]
            libraryModel.append({ name: brush.name, size: brush.size, opacity: brush.opacity, flow: brush.flow,
                                    spacing: brush.spacing, hardness: brush.hardness, roundness: brush.roundness,
                                    angle: brush.angle, jitter: brush.jitter, eraser: brush.eraser })
        }
    }

    Flow {
        anchors.fill: parent
        spacing: 5

        Repeater {
            model: libraryModel
            delegate: Button {
                width: 50
                height: 50
                text: name
                isDefault: index == currentBrush
                onClicked: changeBrushSettings(index)
                style: ButtonStyle {
                    label: Text {
                        text: control.text
                        horizontalAlignment: Text.AlignHCenter
                        verticalAlignment: Text.AlignVCenter
                        wrapMode: Text.WordWrap
                        elide: Text.ElideRight
                    }

                    background: Rectangle {
                        implicitWidth: 50
                        implicitHeight: 50
                        border.color: control.isDefault ? "red" : "#888"
                        radius: 4
                        antialiasing: true
                        gradient: Gradient {
                            GradientStop { position: 0 ; color: control.pressed ? "#ccc" : "#eee" }
                            GradientStop { position: 1 ; color: control.pressed ? "#aaa" : "#ccc" }
                        }
                    }
                }
            }
        }

        ListModel {
            id: libraryModel
        }
    }
}
