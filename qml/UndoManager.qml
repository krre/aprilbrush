import QtQuick 2.0
import "components"
import "undo.js" as Undo

Window {
    id: root
    title: "Undo History"
    property alias currentUndo: undoView.currentIndex
    property alias undoView: undoView
    property int undoDeep: 50
    property int prevIndex: -1
    property var commandArray: [] // array for saving undo/redo command (they don't work from ListModel)
    property bool endList: false
    property bool newUndo: false

    parent: main
    visible: (index == pagesView.currentIndex) && undoManagerVisible
    x: undoManagerPos.x
    y: undoManagerPos.y
    z: 5
    width: undoManagerSize.width
    height: undoManagerSize.height
    autoClose: false
    onReleased: undoManagerPos = Qt.point(x, y)
    onClosed: undoManagerVisible = false
    onResized: undoManagerSize = Qt.size(width, height)

    function add(commandUndo) {
        if (undoView.currentIndex < undoSet.count - 1) {
            undoSet.remove(undoView.currentIndex + 1, undoSet.count - undoView.currentIndex - 1)
            commandArray.length = undoView.currentIndex + 1
        }
        if (undoSet.count === undoDeep) {
            endList = true
            undoSet.remove(0)
            commandArray.shift()
        }

        newUndo = true
        undoSet.append({ name: commandUndo.name })
        commandArray.push(commandUndo)
        undoView.currentIndex = undoSet.count - 1
        endList = false
        newUndo = false
    }

    function run(index) {
        if ((index < prevIndex) && !endList) {
            for (var i = prevIndex; i > index; i--) {
                commandArray[i - 1].undo()
            }
        }

        if (index > prevIndex) {
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
            model: undoSet
            delegate: undoDelegate

            highlight: undoSelected
            highlightMoveDuration: 1

            width: parent.width
            height: root.height - 45

            orientation: ListView.Vertical
            clip: true
            spacing: 4
            onCurrentIndexChanged: if (!newUndo) run(currentIndex)
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
