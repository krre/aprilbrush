import QtQuick 2.0
import "components"
import "brushlib.js" as BrushLib

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
            Component.onCompleted: {
                BrushLib.loadBrushPack()
                brushSettings.size.init = libraryModel.get(0).size
                brushSettings.opaque.init = libraryModel.get(0).opaque
                brushSettings.spacing.init = libraryModel.get(0).spacing
                brushSettings.hardness.init = libraryModel.get(0).hardness
                brushSettings.roundness.init = libraryModel.get(0).roundness
                brushSettings.angle.init = libraryModel.get(0).angle
                brushSettings.jitter.init = libraryModel.get(0).jitter
            }
        }

        Component {
            id: brushDelegate
            ListItem {
                text: name
                width: 50
                height: 50
                closable: false
                color: GridView.isCurrentItem ? "transparent" : "lightgray"
                onClicked: {
                    libraryView.currentIndex = index
                    brushSettings.size.init = size
                    brushSettings.opaque.init = opaque
                    brushSettings.spacing.init = spacing
                    brushSettings.hardness.init = hardness
                    brushSettings.roundness.init = roundness
                    brushSettings.angle.init = angle
                    brushSettings.jitter.init = jitter
                }
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
        }
    }
}
