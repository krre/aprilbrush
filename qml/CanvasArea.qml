import QtQuick 2.0
import PaintItem 1.0

Item {
    id: root
    property alias pathView: pathView

    parent: checkerBoard
    width: parent.width
    height: parent.height
    x: imageSize.width / 2
    y: imageSize.height / 2
    visible: index == pagesView.currentIndex
    z: 2

    PathView {
        id: pathView
        model: layerSet
        delegate: paintSpaceDelegate

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
            width: root.width
            height: root.height
            contentsSize.width: imageSize.width
            contentsSize.height: imageSize.height
            fillColor: colorImage
            z: 1000 - index
            visible: enable

            MouseArea {
                anchors.fill: parent
                onPressed: { brush.setSource(pathView.currentItem); brush.paintDab(mouseX, mouseY) }
                onReleased: brush.setTouch(false)
                onPositionChanged: { brush.paintDab(mouseX, mouseY) }
            }
        }
    }
}
