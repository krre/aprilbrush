import QtQuick 2.0
import QtQuick.Window 2.0
import PaintItem 1.0

Item {
    property alias pathView: pathView
    parent: main
    visible: index == pagesView.currentIndex
    z: 2

    width: main.width
    height: main.height

    PathView {
        id: pathView
        model: layerSet
        delegate: paintSpaceDelegate

        anchors.centerIn: parent
        path: Path {
            PathAttribute { name: "z"; value: 9999.0 }
            PathLine { x: 0; y: 0 }
            PathAttribute { name: "z"; value: 0.0 }
        }
        currentIndex: layerManager.currentLayer
    }

    Component {
        id: paintSpaceDelegate

        PaintSpace {
            id: paintSpace
            width: main.width
            height: main.height
            contentsSize.width: Screen.width
            contentsSize.height: Screen.height
            fillColor: colorImage
            z: 1000 - index
            visible: enable

            MouseArea {
                anchors.fill: parent
                onPressed: brush.paintDab(mouseX, mouseY)
                onReleased: brush.setTouch(false)
                onPositionChanged: brush.paintDab(mouseX, mouseY)
            }
        }
    }
}
