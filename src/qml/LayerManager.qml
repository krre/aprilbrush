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
    property alias tableView: tableView
    title: qsTr("Layers")
    objectName: "layerManager"
    storage: { var list = defaultStorage(); return list }

    function addLayer(name, color) {
        var insertIndex = tableView.currentRow < 0 ? 0 : tableView.currentRow
        layerModel.insert(insertIndex, { name: name, color: color, layerVisible: true, blocked: false })
        tableView.currentRow = insertIndex
    }

    function deleteLayer(index) {
        if (index) {
            layerModel.remove(index)
        } else {
            layerModel.remove(tableView.currentRow)
        }
    }

    ColumnLayout {
        anchors.fill: parent

        TableViewBase {
            id: tableView
            Layout.fillWidth: true
            Layout.fillHeight: true
            model: currentTab ? currentTab.layerModel : []
//            itemDelegate: layerDelegate
            headerVisible: false

            TableViewColumn {
                role: "name"
            }
        }

//        Component {
//            id: layerDelegate

            /*

            Rectangle {
                //                width: ListView.view.width
//                height: 60
                color: styleData.selected ? "#7d91f5" : "transparent"
//                Component.onCompleted: layerModel.set(styleData.row, { "item": this })

                RowLayout {
                    anchors.fill: parent
                    anchors.margins: 5
                    spacing: 5

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
                            visible: model.visibled
                        }

                        MouseArea {
                            anchors.fill: parent
                            onClicked: layerModel.setProperty(styleData.row, "visibled", !model.visibled)
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
                            visible: model.blocked
                        }

                        MouseArea {
                            anchors.fill: parent
                            onClicked: layerModel.setProperty(styleData.row, "blocked", !model.blocked)
                        }
                    }

                    Item {
                        Layout.fillWidth: true
                        Layout.preferredHeight: parent.height

                        Text {
                            text: model.name
                            width: parent.width
                            anchors.verticalCenter: parent.verticalCenter
                            visible: !layerTextEdit.focus
                        }

                        MouseArea {
                            anchors.fill: parent
                            onClicked: tableView.currentRow = styleData.row
                            onDoubleClicked: layerTextEdit.focus = true
                        }

                        TextField {
                            id: layerTextEdit
                            property string lastText

                            width: parent.width
                            anchors.verticalCenter: parent.verticalCenter
                            text: model.name
                            visible: focus

                            onFocusChanged: {
                                if (focus){
                                    lastText = text
                                    selectAll()
                                }
                            }

                            onEditingFinished: {
                                layerModel.setProperty(styleData.row, "name", text)
                                parent.forceActiveFocus()
                            }

                            Keys.onEscapePressed: {
                                text = lastText
                                parent.forceActiveFocus()
                            }
                        }
                    }
                }
            }*/
//        }

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
