import QtQuick 2.0
import "components"
import PaintItem 1.0

Item {
    id: root
    property alias pathView: pathView
    property real zoom: 1
    property point pan: Qt.point(0, 0)

    parent: checkerBoard
    width: parent.width
    height: parent.height
    x: imageSize.width / 2
    y: imageSize.height / 2
    z: 0
    visible: index == pagesView.currentIndex
    focus: index == pagesView.currentIndex

    Keys.onPressed: {
        if (event.key == Qt.Key_Delete) { brush.setSource(pathView.currentItem); brush.clear() }
        if (event.key == Qt.Key_S) brushSettings.visible = !brushSettings.visible
        if (event.key == Qt.Key_C) colorPicker.visible = !colorPicker.visible
        if (event.key == Qt.Key_L) layerManagerVisible = !layerManagerVisible
        if (event.key == Qt.Key_P) brushLibrary.visible = !brushLibrary.visible
        if (event.key == Qt.Key_Plus) zoom *= 1.5
        if (event.key == Qt.Key_Minus) zoom /= 1.5
        if (event.key == Qt.Key_0) zoom = 1
    }

    CheckerBoard {
        id: checkerBoard
        parent: main
        cellSide: 30
        width: imageSize.width
        height: imageSize.height
        anchors.centerIn: parent
        visible: index == pagesView.currentIndex
        scale: zoom
    }

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
