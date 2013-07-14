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

Window {
    id: root
    title: "Undo History"
    autoClose: false
    property alias currentUndo: undoView.currentIndex
    property alias undoView: undoView
    property int undoDeep: 50
    property int prevIndex: -1
    property var commandArray: [] // array for saving undo/redo command (they don't work from ListModel)
    property bool endList: false
    property bool newUndo: false
/*
    x: settings.undoManager.position.x
    y: settings.undoManager.position.y
    z: settings.undoManager.position.z
    width: settings.undoManager.size.width
    height: settings.undoManager.size.height
    visible: (index == pagesView.currentIndex) && settings.undoManager.visible

    onReleased: {
        settings.undoManager.position.x = x
        settings.undoManager.position.y = y
        settings.undoManager.position.z = z

    }
    onResized: {
        settings.undoManager.size.width = width
        settings.undoManager.size.height = height
    }
    onClosed: settings.undoManager.visible = false
*/
    x: undoManagerPos.x
    y: undoManagerPos.y
    z: undoManagerPos.z
    width: undoManagerSize.width
    height: undoManagerSize.height
    visible: (index == pagesView.currentIndex) && undoManagerVisible

    onReleased: {
        undoManagerPos = Qt.vector3d(x, y, z)
    }
    onResized: {
        undoManagerSize = Qt.size(width, height)
    }
    onClosed: undoManagerVisible = false

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
            for (var i = prevIndex; i < index; i++) {
                commandArray[i + 1].redo()
            }
        }
        prevIndex = index
    }

    Item {
        anchors.fill: parent

        ListView {
            id: undoView
            model: undoModel
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
