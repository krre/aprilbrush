import QtQuick 2.0
import "components"

Window {
    id: root
    title: "Undo History"
    property alias currentUndo: undoView.currentIndex
    property alias undoView: undoView

    Item {
        anchors.fill: parent

        ListView {
            id: undoView
            model: undoModel
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
