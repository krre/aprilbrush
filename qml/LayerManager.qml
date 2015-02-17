/* AprilBrush - Digital Painting Software
 * Copyright (C) 2012-2014 Vladimir Zarypov <krre31@gmail.com>
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation;
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 */

import QtQuick 2.4
import QtQuick.Controls 1.3
import QtQuick.Layouts 1.1
import "components"
import "utils.js" as Utils
import "undo.js" as Undo

ToolWindow {
    id: root
    title: qsTr("Layers")
    property alias layerView: layerView
    property int layerNameIndexCounter: 1
    objectName: "layerManager"
    storage: {
        var list = defaultStorage()
        return list
    }

    function addLayer(name) {
        undoManager.add(Undo.addLayer(name ? name : qsTr("Layer") + " " + layerNameIndexCounter++))
    }

    function addBackground() {
        var layerObj = defaultLayer()
        layerObj.name = qsTr("Background")
        layerObj.isBackground = true
        layerModel.append(layerObj)
        canvasArea.bgColor = "white"
    }

    function defaultLayer() {
        return {
            name: "None",
            isVisible: true,
            isLock: false,
            isBackground: false
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
                onCurrentItemChanged: {
                    if (currentIndex == count - 1) {
                        // avoid selecting background layer
                        currentIndex = currentIndex - 1
                    }
                }
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
                        if (layerView.currentIndex !== index && index !== layerView.count - 1) {
                            undoManager.add(Undo.changeLayer(layerView.currentIndex, index))
                            layerView.currentIndex = index
                        }
                    }
                    onDoubleClicked: {
                        if (index !== layerView.count - 1) {
                            layerTextEdit.forceActiveFocus()
                        }
                    }
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

                        CheckBox {
                            text: qsTr("Visible")
                            checked: isVisible
                            onClicked: undoManager.add(Undo.changeIsVisibileLayer(index))
                        }

                        CheckBox {
                            text: qsTr("Lock")
                            checked: isLock
                            onClicked: undoManager.add(Undo.changeIsLockLayer(index))
                            visible: !isBackground
                        }

                        RowLayout {
                            visible: isBackground
                            spacing: 5

                            Rectangle {
                                width: 15
                                height: 15
                                radius: width / 2
                                color: canvasArea.bgColor
                                border.color: "#474747"
                            }

                            Label { text: qsTr("Color") }

                            MouseArea {
                                anchors.fill: parent
                                onClicked: colorDialog.open()
                            }
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
