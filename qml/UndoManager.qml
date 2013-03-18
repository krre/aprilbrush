import QtQuick 2.0
import "components"

Window {
    id: root
    title: "Undo History"
    property alias currentUndo: undoView.currentIndex
    property alias undoView: undoView

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

    Item {
        anchors.fill: parent

        ListView {
            id: undoView
            model: undoSet
            delegate: undoDelegate

            highlight: undoSelected
            highlightMoveDuration: 1

            width: parent.width
            height: 150

            orientation: ListView.Vertical
            clip: true
            spacing: 4
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
