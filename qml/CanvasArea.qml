import QtQuick 2.0
import "components"
import PaintedItem 1.0
import "utils.js" as Utils
import "undo.js" as Undo

Item {
    id: root
    property alias pathView: pathView
    property real zoom: 1
    property bool panMode: false
    property point pan: Qt.point(0, 0)
    property int mirror: 1
    property real rotation: 0
    property bool saved: false
    property string oraPath

    parent: checkerBoard
    width: parent.width
    height: parent.height
    x: imageSize.width / 2
    y: imageSize.height / 2
    z: 0
    visible: index == pagesView.currentIndex
    focus: index == pagesView.currentIndex

    Component.onCompleted: {
        undoManager.add(new Undo.start())
    }

    Keys.onPressed: {
        switch (event.key) {
            case Qt.Key_B: eraserMode = false; break
            case Qt.Key_E: eraserMode = true; break
            case Qt.Key_Delete:
                undoManager.add(new Undo.clear())
                brush.setSource(pathView.currentItem)
                brush.clear()
                break
            case Qt.Key_S: if (!event.modifiers) brushSettings.visible = !brushSettings.visible; break
            case Qt.Key_C: colorPicker.visible = !colorPicker.visible; break
            case Qt.Key_L: layerManagerVisible = !layerManagerVisible; break
            case Qt.Key_U: undoManagerVisible = !undoManagerVisible; break
            case Qt.Key_P: brushLibrary.visible = !brushLibrary.visible; break
            case Qt.Key_D: fileDialog.visible = !fileDialog.visible; break

            case Qt.Key_Plus: zoom *= 1.5; break
            case Qt.Key_Minus: zoom /= 1.5; break
            case Qt.Key_0: zoom = 1; pan = Qt.point(0, 0); mirror = 1; rotation = 0; break
            case Qt.Key_Space: panMode = true; break
            case Qt.Key_F: mirror *= -1; break
            case Qt.Key_R: rotation += 90; break
        }
        if ((event.modifiers & Qt.ControlModifier) && (event.key === Qt.Key_Z)) undoManager.undoView.decrementCurrentIndex()
        if ((event.modifiers & Qt.ControlModifier) && (event.key === Qt.Key_Y)) undoManager.undoView.incrementCurrentIndex()
        if ((event.modifiers & Qt.ControlModifier) && (event.key === Qt.Key_S)) {
            if (oraPath === "") {
                fileDialog.openMode = false;
                fileDialog.visible = true
            }
            else
                Utils.saveOra()
            return
        }
        if ((event.modifiers & Qt.AltModifier) && (event.key === Qt.Key_S)) {
            fileDialog.openMode = false;
            fileDialog.visible = true
            return
        }

        if ((event.modifiers & Qt.ControlModifier) && (event.key === Qt.Key_O)) {
            fileDialog.openMode = true;
            fileDialog.visible = true
            return
        }
    }

    Keys.onReleased: if (event.key === Qt.Key_Space) panMode = false

    CheckerBoard {
        id: checkerBoard
        parent: main

        x: (parent.width - imageSize.width) / 2 + pan.x
        y: (parent.height - imageSize.height) / 2 + pan.y

        cellSide: 30
        width: imageSize.width
        height: imageSize.height
        visible: index == pagesView.currentIndex
        transform: [
            Scale { origin.x: width / 2; origin.y: height / 2; xScale: zoom * mirror; yScale: zoom },
            Rotation { origin.x: width / 2; origin.y: height / 2; angle: rotation }
        ]

        MouseArea {
            // Used two mouse area, because a strange bug does not allow to use a brush and pan in one
            property point grabPoint: Qt.point(0, 0)
            anchors.fill: parent
            hoverEnabled: panMode
            onPositionChanged: {
                pan.x += (mouseX - grabPoint.x) * zoom * mirror
                pan.y += (mouseY - grabPoint.y) * zoom
            }
            visible: panMode
            onVisibleChanged: grabPoint = Qt.point(mouseX, mouseY)
        }
    }

    PathView {
        id: pathView
        model: layerSet
        delegate: paintSpaceDelegate

        highlightRangeMode: PathView.NoHighlightRange
        path: Path {
            PathAttribute { name: "z"; value: 9999.0 }
            PathLine { x: 0; y: 0 }
            PathAttribute { name: "z"; value: 0.0 }
        }
        currentIndex: layerManager.currentLayer
        //onCurrentIndexChanged: console.log("pathview index: " + currentIndex)
    }

    Component {
        id: paintSpaceDelegate

        PaintedItem {
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
                onReleased: {
                    brush.setTouch(false);
                    undoManager.add(new Undo.paint())
                }
                onPositionChanged: brush.paintDab(mouseX, mouseY)
                visible: !panMode
            }
        }
    }
}
