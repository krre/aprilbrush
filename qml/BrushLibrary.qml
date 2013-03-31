import QtQuick 2.0
import "components"

Window {
    id: root
    title: "Brush Library"

    Item {
        anchors.fill: parent

        GridView {
            id: libraryView
            model: libraryModel
            delegate: brushDelegate

            width: parent.width
            height: root.height - 65
            cellWidth: 56
            cellHeight: 56
            highlight: brushSelected
            highlightMoveDuration: 1
            clip: true
        }

        Component {
            id: brushDelegate
            ListItem {
                text: name
                width: 50
                height: 50
                closable: false
                color: GridView.isCurrentItem ? "transparent" : "lightgray"
                onClicked: libraryView.currentIndex = index
            }
        }

        Component {
            id: brushSelected
            ListItemComponent {
                width: 50
                height: 50
            }
        }

        ListModel {
            id: libraryModel
            ListElement {name: "Active"}
            ListElement {name: "Default"}
            ListElement {name: "Big"}
            ListElement {name: "Little"}
            ListElement {name: "Ellipse"}
            ListElement {name: "Eraser"}
        }
    }
}
