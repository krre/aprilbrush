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
import AprilBrushLib 1.0
import "components"
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
    property bool focusBind: true
    property string cursorName: "Paint"
    property bool ctrlMode: false

    parent: checkerBoard
    width: parent.width
    height: parent.height
    x: imageSize.width / 2
    y: imageSize.height / 2
    z: 0
    visible: index == pagesView.currentIndex
    Binding on focus {
        when: focusBind
        value: index == pagesView.currentIndex
    }

    Component.onCompleted: {
        undoManager.add(new Undo.start())
    }

    Keys.onPressed: {
        switch (event.key) {
            case Qt.Key_B: eraserMode = false; break
            case Qt.Key_E: eraserMode = true; break
            case Qt.Key_Delete:
                undoManager.add(new Undo.clear())
                brushEngine.clear()
                pathView.currentItem.update()
                break
            case Qt.Key_Plus: zoom *= 1.5; break
            case Qt.Key_Minus: zoom /= 1.5; break
            case Qt.Key_0: zoom = 1; pan = Qt.point(0, 0); mirror = 1; rotation = 0; break
            case Qt.Key_Space: if (!event.isAutoRepeat) panMode = true; break
            case Qt.Key_C: if (!event.isAutoRepeat) dockMode = true; break
            case Qt.Key_M: mirror *= -1; break
            case Qt.Key_R: rotation += 90; break
            case Qt.Key_F: undoManager.add(new Undo.fillColor()); break
            case Qt.Key_Z: undoManager.undoView.decrementCurrentIndex(); break
            case Qt.Key_X: undoManager.undoView.incrementCurrentIndex(); break
        }

        if ((event.modifiers & Qt.ControlModifier) && (event.key === Qt.Key_S)) {
            if (oraPath === "") {
                fileDialog.mode = 1; // Save mode
                fileDialog.visible = true
            }
            else
                Utils.saveOra()
        }

        if ((event.modifiers & Qt.ShiftModifier) && (event.key === Qt.Key_S)) {
            fileDialog.mode = 1; // Save mode
            fileDialog.open()
        }

        if ((event.modifiers & Qt.ControlModifier) && (event.key === Qt.Key_O)) {
            fileDialog.mode = 0; // Open mode
            fileDialog.open()
        }
        if ((event.modifiers & Qt.ControlModifier) && (event.key === Qt.Key_E)) {
            fileDialog.mode = 2; // Export mode
            fileDialog.open()
        }

        if ((event.modifiers & Qt.ControlModifier) && (event.key === Qt.Key_Space)) {
            if (!event.isAutoRepeat) dockMode = true
        }

        if (event.modifiers & Qt.ControlModifier)
            ctrlMode = true
    }

    Keys.onReleased: {
        if (Qt.ControlModifier)
            ctrlMode = false
        if (event.key === Qt.Key_Space) { if (!event.isAutoRepeat) panMode = false }
        if (event.key === Qt.Key_C) { if (!event.isAutoRepeat) dockMode = false }
    }

    CheckerBoard {
        id: checkerBoard
        parent: workArea

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
    }

    PathView {        
        id: pathView
        model: layerModel
        delegate: paintedItemDelegate

        highlightRangeMode: PathView.NoHighlightRange
        path: Path {
            PathAttribute { name: "z"; value: 9999.0 }
            PathLine { x: 0; y: 0 }
            PathAttribute { name: "z"; value: 0.0 }
        }
        currentIndex: layerManager.currentLayerIndex
    }

    Component {
        id: paintedItemDelegate

        PaintedItem {
            id: paintedItem
            objectName: layerId
            width: root.width
            height: root.height
            imageProcessor: imgProcessor
            z: 1000 - index
            visible: enable

            MouseArea {
                property real zoomItem: zoom
                property bool panModeItem: panMode
                property point grabPoint

                anchors.fill: parent
                hoverEnabled: true
                onHoveredChanged: containsMouse ? paintedItem.setItemCursor(cursorName, brushSettings.size.value * zoom) : paintedItem.unSetItemCursor()
                onZoomItemChanged: containsMouse ? paintedItem.setItemCursor(cursorName, brushSettings.size.value * zoom) : paintedItem.unSetItemCursor()
                onPanModeItemChanged: if (panModeItem) {
                                          cursorName = "OpenHand";
                                          paintedItem.setItemCursor(cursorName, 0)
                                      }
                                      else {
                                          cursorName = "Paint";
                                          paintedItem.setItemCursor(cursorName, brushSettings.size.value * zoom)
                                      }
                onPressed:
                    if (panMode) {
                        cursorName = "ClosedHand"
                        paintedItem.setItemCursor(cursorName, 0)
                        grabPoint = Qt.point(mouseX, mouseY)
                    }
                    else {
                        if (ctrlMode)
                            colorPicker.color = Utils.pickColor(Qt.point(mouseX, mouseY))
                        else {
                            brushEngine.setTouch(Qt.point(mouseX, mouseY))
                            brushEngine.paintDab(Qt.point(mouseX, mouseY))
                        }
                    }
                onReleased:
                    if (panMode) {
                        cursorName = "OpenHand"
                        paintedItem.setItemCursor(cursorName, 0)
                    }
                    else
                        if (!ctrlMode)
                        {
                            brushEngine.setUnTouch();
                            undoManager.add(new Undo.paint())
                        }
                onPositionChanged:
                    if (pressed) {
                        if (panModeItem) {
                            pan.x += (mouseX - grabPoint.x) * zoom * mirror
                            pan.y += (mouseY - grabPoint.y) * zoom
                        }
                        else {
                            if (ctrlMode)
                                colorPicker.color = Utils.pickColor(Qt.point(mouseX, mouseY))
                            else
                                brushEngine.paintDab(Qt.point(mouseX, mouseY))
                        }
                    }
            }
        }
    }
}
