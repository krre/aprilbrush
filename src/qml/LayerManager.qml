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

import QtQuick 2.1
import QtQuick.Controls 1.0
import QtQuick.Layouts 1.0
import "components"
import "style"
import "utils.js" as Utils
import "undo.js" as Undo

ToolWindow {
    id: root
    property alias layerView: layerView
    title: "Layers"
    objectName: "layerManager"
    storage: { var list = defaultStorage(); return list }

    function addLayer(name, color) {
        var insertIndex = layerView.currentIndex < 0 ? 0 : layerView.currentIndex
        layerModel.insert(insertIndex, { name: name, color: color, visibled: true, blocked: false })
        layerView.currentIndex = insertIndex
    }

    ColumnLayout {
        anchors.fill: parent

        ListView {
            id: layerView
            Layout.fillHeight: true
            Layout.fillWidth: true
            model: layerModel
            delegate: layerDelegate
            spacing: 5
            clip: true
            focus: true
        }

        Component {
            id: layerDelegate

            RowLayout {
                property alias thumbnail: thumbnail
                width: ListView.view.width
                height: 50
                opacity: ListView.isCurrentItem ? 1.0 : 0.6
                spacing: 5

                Column {
                    width: 20
                    height: parent.height
                    spacing: 3
                    anchors.verticalCenter: parent.verticalCenter

                    Rectangle {
                        width: 15
                        height: 15
                        radius: width / 2
                        antialiasing: true
                        color: "transparent"
                        border.color: "gray"

                        Rectangle {
                            id: layerVisible
                            width: 7
                            height: 7
                            anchors.centerIn: parent
                            radius: width / 2
                            antialiasing: true
                            color: "white"
                            visible: visibled
                        }

                        MouseArea {
                            anchors.fill: parent
                            onClicked: layerModel.setProperty(index, "visibled", !visibled)
                        }
                    }

                    Rectangle {
                        width: 15
                        height: 15
                        color: "transparent"
                        border.color: "gray"

                        Rectangle {
                            id: layerBlocked
                            width: 7
                            height: 7
                            anchors.centerIn: parent
                            color: "white"
                            visible: blocked
                        }

                        MouseArea {
                            anchors.fill: parent
                            onClicked: layerModel.setProperty(index, "blocked", !blocked)
                        }
                    }
                }

                Rectangle {
                    Layout.preferredWidth: 80
                    Layout.preferredHeight: parent.height
                    color: "transparent"
                    border.color: "gray"

                    Canvas {
                        id: thumbnail
                        width: parent.width - 2
                        height: parent.height - 2
                        anchors.centerIn: parent

                        onAvailableChanged: if (true) { paintThumbnail() }

                        function paintThumbnail() {
                            var ctx = getContext("2d")
                            ctx.clearRect(0, 0, width, height)
                            var thumbnail = canvasView.currentItem.currentItem.getContext("2d").getImageData(0, 0, imageSize.width, imageSize.height)
                            ctx.drawImage(thumbnail, 0, 0, width, height)
                            requestPaint()
                        }

                        MouseArea {
                            anchors.fill: parent
                            onClicked: {
                                layerTextEdit.focus = false
                                layerView.currentIndex = index
                            }
                        }
                    }


                }


                Item {
                    Layout.fillWidth: true
                    Layout.preferredHeight: parent.height

                    Text {
                        text: name
                        width: parent.width
                        color: "white"
                        anchors.verticalCenter: parent.verticalCenter
                        visible: !layerTextEdit.focus
                    }

                    MouseArea {
                        anchors.fill: parent
                        onClicked: layerView.currentIndex = index
                        onDoubleClicked: layerTextEdit.focus = true
                    }

                    TextEdit {
                        id: layerTextEdit
                        width: parent.width
                        anchors.verticalCenter: parent.verticalCenter
                        text: name
                        color: "white"
                        cursorPosition: text.length
                        visible: focus
                        onTextChanged: if (text[text.length - 1] === "\n") {
                                           text = text.replace("\n", "")
                                           focus = false
                                       }
                        onFocusChanged: if (!focus) { layerModel.setProperty(index, "name", text) }
                    }
                }

                CloseButton {
                    anchors.top: parent.top
                    anchors.topMargin: 2
                    anchors.right: parent.right
                    anchors.rightMargin: 5
                    onClicked: layerModel.remove(index)
                }
            }
        }

        RowLayout {
            spacing: 2

            Button {
                Layout.fillWidth: true
                text: qsTr("New")
                onClicked: {
                    addLayer("Layer", "transparent")
//                    undoManager.add(new Undo.addLayer())
                }
                enabled: mainModel.count > 0
                style: ButtonStyle {}

            }

            Button {
                Layout.fillWidth: true
                text: qsTr("Up")
                onClicked: {
                    if (currentLayerIndex > 0) {
                        layerModel.move(currentLayerIndex, currentLayerIndex - 1, 1)
//                        undoManager.add(new Undo.raiseLayer())
                    }
                }
                style: ButtonStyle {}
            }

            Button {
                Layout.fillWidth: true
                text: qsTr("Down")
                onClicked: {
                    if (currentLayerIndex < layerView.count - 1) {
                        layerModel.move(currentLayerIndex, currentLayerIndex + 1, 1)
//                        undoManager.add(new Undo.lowerLayer())
                    }
                }
                style: ButtonStyle {}
            }

            Button {
                Layout.fillWidth: true
                text: qsTr("Merge")
                onClicked: {
                    if ((layerView.count > 1) && (currentLayerIndex < layerView.count - 1)) {
//                        undoManager.add(new Undo.mergeLayer())
                    }
                }
                style: ButtonStyle {}
            }

            Button {
                Layout.fillWidth: true
                text: qsTr("Clone")
                onClicked: {
//                    undoManager.add(new Undo.cloneLayer())
                }
                style: ButtonStyle {}
            }
        }
    }
}
