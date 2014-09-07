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

import QtQuick 2.3
import QtQuick.Controls 1.2
import QtQuick.Layouts 1.1
import "components"
import "utils.js" as Utils
import "undo.js" as Undo

ToolWindow {
    id: root
    title: qsTr("Layers")
    property alias layerView: layerView
    property int nameIndexCounter: 1
    objectName: "layerManager"
    storage: { var list = defaultStorage(); return list }

    function addLayer() {
        var name = qsTr("Layer") + " " + nameIndexCounter
        undoManager.add(Undo.addLayer(name))
        nameIndexCounter++
    }

    function addBackground() {
        var layerObj = defaultLayer()
        layerObj.name = qsTr("Background")
        layerObj.isBackground = true
        layerModel.append(layerObj)
    }

    function defaultLayer() {
        return { name: "None", isVisible: true, isBlocked: false, isBackground: false }
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
               Component.onCompleted: layerModel.set(index, { "item": this })

               RowLayout {
                    anchors.fill: parent
                    anchors.margins: 5
                    spacing: 5

                    ColumnLayout {
                        Layout.preferredWidth: 20
                        Layout.fillHeight: true

                        Rectangle {
                            width: 15
                            height: 15
                            radius: width / 2
                            antialiasing: true
                            color: "transparent"
                            border.color: "#474747"

                            Rectangle {
                                id: layerVisible
                                width: 7
                                height: 7
                                anchors.centerIn: parent
                                radius: width / 2
                                antialiasing: true
                                color: "#474747"
                                visible: isVisible
                            }

                            MouseArea {
                                anchors.fill: parent
                                onClicked: layerModel.setProperty(index, "isVisible", !isVisible)
                            }
                        }

                        Rectangle {
                            width: 15
                            height: 15
                            color: isBackground ? currentTab.bgColor : "transparent"
                            border.color: "#474747"

                            Rectangle {
                                id: layerBlocked
                                width: 7
                                height: 7
                                anchors.centerIn: parent
                                color: "#474747"
                                visible: isBlocked && !isBackground
                            }

                            MouseArea {
                                anchors.fill: parent
                                onClicked: {
                                    if (isBackground) {
                                        colorDialog.open()

                                    } else {
                                        layerModel.setProperty(index, "isBlocked", !isBlocked)
                                    }
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
                            anchors.verticalCenter: parent.verticalCenter
                            visible: !layerTextEdit.focus
                        }

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
                                    layerTextEdit.focus = true
                                }
                            }
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
                                if (focus){
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
