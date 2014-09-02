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
import "components"
import "undo.js" as Undo

ToolWindow {
    id: root
    title: qsTr("Undo History")
    property alias currentUndo: undoView.currentRow
    property alias undoView: undoView
    property int undoDeep: 50
    property int prevIndex: -1
    property var commandArray: [] // array for saving undo/redo command (they don't work from ListModel)

    objectName: "undoManager"
    storage: { var list = defaultStorage(); return list }

    function add(commandUndo) {
        if (undoView.currentRow < undoModel.count - 1) {
            undoModel.remove(undoView.currentRow + 1, undoModel.count - undoView.currentRow - 1)
            commandArray.length = undoView.currentRow + 1
        }
        if (undoModel.count === undoDeep) {
            undoModel.remove(0)
            commandArray.shift()
        }

        undoModel.append({ name: commandUndo.name })
        commandArray.push(commandUndo)
        undoView.currentRow = undoModel.count - 1
    }

    function clear() {
        commandArray = []
        undoModel.clear()
        prevIndex = -1
        add(Undo.start())
    }

    function run(index) {
        if (index < prevIndex) {
            for (var i = prevIndex; i > index; i--) {
                commandArray[i].undo()
            }
        }

        if (index > prevIndex) {
            for (i = prevIndex; i < index; i++) {
                commandArray[i + 1].redo()
            }
        }
        prevIndex = index
    }

    TableViewBase {
        id: undoView
        anchors.fill: parent
        model: undoModel
        onCurrentRowChanged: run(currentRow)

        TableViewColumn {
            role: "name"
        }
    }
}
