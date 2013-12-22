/* AprilBrush - Digital Painting Software
 * Copyright (C) 2012-2013 Vladimir Zarypov <krre@mail.ru>
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
import "components"
import "undo.js" as Undo

ToolWindow {
    id: root
    text: "Undo History"
    property alias currentUndo: undoView.currentIndex
    property alias undoView: undoView
    property int undoDeep: 50
    property int prevIndex: -1
    property var commandArray: [] // array for saving undo/redo command (they don't work from ListModel)
    property bool endList: false
    property bool newUndo: false

    function add(commandUndo) {
        if (undoView.currentIndex < undoModel.count - 1) {
            undoModel.remove(undoView.currentIndex + 1, undoModel.count - undoView.currentIndex - 1)
            commandArray.length = undoView.currentIndex + 1
        }
        if (undoModel.count === undoDeep) {
            endList = true
            undoModel.remove(0)
            commandArray.shift()
        }

        newUndo = true
        undoModel.append({ name: commandUndo.name })
        commandArray.push(commandUndo)
        undoView.currentIndex = undoModel.count - 1
        endList = false
        newUndo = false
    }

    function run(index) {
        if ((index < prevIndex) && !endList) {
            for (var i = prevIndex; i > index; i--) {
                commandArray[i].undo()
            }
        }

        if ((index > prevIndex) && !newUndo) {
            for (i = prevIndex; i < index; i++) {
                commandArray[i + 1].redo()
            }
        }
        prevIndex = index
    }

    Item {
        anchors.fill: parent

        ListView {
            id: undoView
            model: pageModel.count > 0 ? pageModel.get(pageView.currentIndex).undoModel : 0
            delegate: undoDelegate

            highlight: undoSelected
            highlightMoveDuration: 1

            width: parent.width
            height: parent.height

            orientation: ListView.Vertical
            clip: true
            spacing: 4
            onCurrentIndexChanged: run(currentIndex)
        }

        Component {
            id: undoDelegate
            ListItem {
                text: name
                color: index == currentUndo ? "transparent" : "lightgray"
                closable: false
                onClicked: {
                    currentUndo = index
                }
            }
        }

        Component {
            id: undoSelected
            ListItemComponent {
                width: undoView.width
            }
        }
    }
}
