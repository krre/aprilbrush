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
import QtQuick.Controls 1.0
import QtQuick.Layouts 1.0
import "components"
import "utils.js" as Utils
import "undo.js" as Undo

ToolWindow {
    id: root
    property alias layerView: layerView
    title: qsTr("Layers")
    objectName: "layerManager"
    storage: { var list = defaultStorage(); return list }

    function addLayer(name, color) {
        var insertIndex = layerView.currentIndex < 0 ? 0 : layerView.currentIndex
        layerModel.insert(insertIndex, { name: name, color: color, visibled: true, blocked: false })
        layerView.currentIndex = insertIndex
    }

    function deleteLayer(index) {
        if (index) {
            layerModel.remove(index)
        } else {
            layerModel.remove(layerView.currentIndex)
        }
    }

    function repaintThumbnails() {
        for (var i = 0; i < layerModel.count; i++) {
//            print(layerModel.get(i).item)
            layerModel.get(i).item.thumbnail.paintThumbnail()
        }
    }

    ColumnLayout {
        anchors.fill: parent

        ScrollView {
            Layout.fillWidth: true
            Layout.fillHeight: true

            ListView {
                id: layerView
                model: currentTab ? currentTab.layerModel : []
                delegate: layerDelegate
                spacing: 0
            }
        }

        Component {
            id: layerDelegate

            Rectangle {
                property alias thumbnail: thumbnail
                width: ListView.view.width
                height: 60
                color: ListView.isCurrentItem ? "#d3a3ee" : "transparent"
                Component.onCompleted: layerModel.set(index, { "item": this })

                RowLayout {
                    anchors.fill: parent
                    anchors.margins: 5
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
                            border.color: "#474747"

                            Rectangle {
                                id: layerVisible
                                width: 7
                                height: 7
                                anchors.centerIn: parent
                                radius: width / 2
                                antialiasing: true
                                color: "#474747"
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
                            border.color: "#474747"

                            Rectangle {
                                id: layerBlocked
                                width: 7
                                height: 7
                                anchors.centerIn: parent
                                color: "#474747"
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
                        border.color: "#474747"

                        Canvas {
                            id: thumbnail
                            width: parent.width - 2
                            height: parent.height - 2
                            anchors.centerIn: parent

                            function paintThumbnail() {
                                var ctx = getContext("2d")
                                var thumbnail = currentTab.canvas.getContext("2d").getImageData(0, 0, imageSize.width, imageSize.height)
                                ctx.drawImage(thumbnail, 0, 0, width, height)
    //                            print("paintThumbnail", currentLayerIndex)
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
                            anchors.verticalCenter: parent.verticalCenter
                            visible: !layerTextEdit.focus
                        }

                        MouseArea {
                            anchors.fill: parent
                            onClicked: layerView.currentIndex = index
                            onDoubleClicked: layerTextEdit.focus = true
                        }

                        TextField {
                            id: layerTextEdit
                            property string lastText

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
                                layerModel.setProperty(index, "name", text)
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
