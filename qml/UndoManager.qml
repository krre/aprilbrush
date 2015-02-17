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
import QtQuick.Controls 1.2
import "components"
import "undo.js" as Undo

ToolWindow {
    id: root
    title: qsTr("Undo History")
    property alias undoView: undoView
    property int undoDeep: 50
    property var commandArray: [] // array for saving undo/redo command (they don't work from ListModel)
    property int prevUndoIndex: -1

    objectName: "undoManager"
    storage: { var list = defaultStorage(); return list }

    function add(commandUndo) {
        if (undoView.currentIndex < undoModel.count - 1) {
            undoModel.remove(undoView.currentIndex + 1, undoModel.count - undoView.currentIndex - 1)
            commandArray.length = undoView.currentIndex + 1
        }
        if (undoModel.count === undoDeep) {
            undoModel.remove(0)
            commandArray.shift()
        }

        undoModel.append({ name: commandUndo.name })
        commandArray.push(commandUndo)
        undoView.currentIndex = undoModel.count - 1
        run(undoView.currentIndex)
        isDirty = true
    }

    function clear() {
        commandArray = []
        undoModel.clear()
        prevUndoIndex = -1
        add(Undo.start())
    }

    function run(index) {
        if (index < prevUndoIndex) {
            for (var i = prevUndoIndex; i > index; i--) {
                commandArray[i].undo()
            }
        }

        if (index > prevUndoIndex) {
            for (i = prevUndoIndex; i < index; i++) {
                commandArray[i + 1].redo()
            }
        }
        prevUndoIndex = index
    }

    ScrollView {
        id: scrollView
        anchors.fill: parent

        ListView {
            id: undoView
            model: undoModel
            spacing: 5
            delegate: Rectangle {
                width: scrollView.width !== scrollView.viewport.width ? scrollView.viewport.width - 5 : scrollView.width
                height: 30
                color: "#e6e6e6"
                border.width: 1
                border.color: ListView.isCurrentItem ? "#7d91f5" : "transparent"

                Text {
                    text: name
                    width: parent.width - 10
                    anchors.centerIn: parent
                }

                MouseArea {
                    anchors.fill: parent
                    onClicked: {
                        if (undoView.currentIndex !== index) {
                            undoView.currentIndex = index
                            run(index)
                        }
                    }
                }
            }
        }
    }
}
