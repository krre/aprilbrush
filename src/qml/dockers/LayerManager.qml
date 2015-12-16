import QtQuick 2.5
import QtQuick.Controls 1.3
import QtQuick.Layouts 1.1
import "../components"
import "../../js/utils.js" as Utils
import "../../js/undo.js" as Undo

Panel {
    id: root
    title: qsTr("Layers")
    property alias layerView: layerView
    property alias currentIndex: layerView.currentIndex
    objectName: "LayerManager"

    function addLayer(name) {
        if (!name) {
            var names = []
            for (var i = 0; i < layerModel.count; i++) {
                names.push(layerModel.get(i).name)
            }

            var counter = 1
            do {
                name = qsTr("Layer") + " " + counter++
            } while(names.indexOf(name) > -1)
        }

        undoManager.add(Undo.addLayer(name))
    }

    function defaultLayer() {
        return {
            name: "None",
            isVisible: true,
            isLock: false,
            canvasItem: null
        }
    }

    ColumnLayout {
        anchors.fill: parent

        ScrollView {
            id: scrollView
            Layout.fillWidth: true
            Layout.fillHeight: true

            ListView {
                id: layerView
                model: layerModel
                delegate: layerDelegate
                spacing: 5
            }
        }

        Component {
            id: layerDelegate

            Rectangle {
                width: scrollView.width !== scrollView.viewport.width ? scrollView.viewport.width - 5 : scrollView.width
                height: 60
                color: "#e6e6e6"
                border.width: 1
                border.color: ListView.isCurrentItem ? "#7d91f5" : "transparent"

                MouseArea {
                    anchors.fill: parent
                    onClicked: {
                        if (layerManager.currentIndex !== index) {
                            undoManager.add(Undo.changeLayer(layerManager.currentIndex, index))
                        }
                    }
                    onDoubleClicked: layerTextEdit.forceActiveFocus()
                }

                ColumnLayout {
                    anchors.fill: parent
                    anchors.margins: 10
                    spacing: 5

                    Item {
                        Layout.fillWidth: true
                        Layout.fillHeight: true

                        Text {
                            text: name
                            width: parent.width
                            anchors.verticalCenter: parent.verticalCenter
                            visible: !layerTextEdit.focus
                        }

                        TextField {
                            id: layerTextEdit
                            property string lastText
                            property int finishedCounter: 0 // TODO: hack to disable double emiting editingFinished() signal

                            width: parent.width
                            anchors.verticalCenter: parent.verticalCenter
                            text: name
                            visible: focus

                            onFocusChanged: {
                                if (focus) {
                                    lastText = text
                                    selectAll()
                                }
                            }

                            onEditingFinished: {
                                if (!finishedCounter) {
                                    if (lastText !== text) {
                                        undoManager.add(Undo.renameLayer(lastText, text))
                                    }
                                    finishedCounter++
                                } else {
                                    finishedCounter = 0
                                }

                                parent.forceActiveFocus()
                            }

                            Keys.onEscapePressed: {
                                text = lastText
                                parent.forceActiveFocus()
                            }
                        }
                    }

                    Row {
                        spacing: 10

                        CheckBox {
                            text: qsTr("Visible")

                            // Strange bug
                            // "checked: isVisible" not works
                            property bool isV: isVisible
                            onIsVChanged: checked = isV
//                            checked: isVisible

                            onClicked: undoManager.add(Undo.changeIsVisibileLayer(index))
                        }

                        CheckBox {
                            text: qsTr("Lock")

                            // Strange bug
                            // "checked: isLock" not works
                            property bool isL: isLock
                            onIsLChanged: checked = isL
//                            checked: isLock

                            onClicked: undoManager.add(Undo.changeIsLockLayer(index))
                        }
                    }
                }
            }
        }

        RowLayout {
            spacing: 2
            Layout.preferredWidth: parent.width

            Button {
                Layout.fillWidth: true
                action: actions.newLayerAction
            }

            Button {
                Layout.fillWidth: true
                action: actions.upLayerAction
            }

            Button {
                Layout.fillWidth: true
                action: actions.downLayerAction
            }

            Button {
                Layout.fillWidth: true
                action: actions.deleteLayerAction
            }
        }
    }
}
