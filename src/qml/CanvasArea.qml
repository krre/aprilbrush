/* AprilBrush - Digital Painting Software
 * Copyright (C) 2012-2014 Vladimir Zarypov <krre31@gmail.com>
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
import ABLib 1.0
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

    width: imageSize.width
    height: imageSize.height

    Keys.onPressed: {
        switch (event.key) {
            case Qt.Key_Plus: zoom *= 1.5; break
            case Qt.Key_Minus: zoom /= 1.5; break
            case Qt.Key_0: zoom = 1; pan = Qt.point(0, 0); mirror = 1; rotation = 0; break
            case Qt.Key_Space: if (!event.isAutoRepeat) panMode = true; break
            case Qt.Key_M: mirror *= -1; break
            case Qt.Key_R: rotation += 90; break
        }

        if (event.modifiers & Qt.ControlModifier)
            ctrlMode = true
    }

    Keys.onReleased: {
        if (Qt.ControlModifier)
            ctrlMode = false
        if (event.key === Qt.Key_Space) { if (!event.isAutoRepeat) panMode = false }
    }

    CheckerBoard {
        id: checkerBoard
        width: imageSize.width
        height: imageSize.height
        anchors.centerIn: parent
        cellSide: 30
        transform: [
            Scale { origin.x: width / 2; origin.y: height / 2; xScale: zoom * mirror; yScale: zoom },
            Rotation { origin.x: width / 2; origin.y: height / 2; angle: rotation }
        ]
    }

    PathView {
        id: pathView
        anchors.centerIn: parent
        model: layerModel
        delegate: paintedItemDelegate

        highlightRangeMode: PathView.NoHighlightRange
        path: Path {
            PathAttribute { name: "z"; value: 9999.0 }
            PathLine { x: 0; y: 0 }
            PathAttribute { name: "z"; value: 0.0 }
        }
        currentIndex: layerManager.layerView.currentIndex
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
                            brushEngine.paintDab(Qt.point(mouseX, mouseY), pressure)
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
                            else {
                                brushEngine.paintDab(Qt.point(mouseX, mouseY), mainRoot.pressure)
//                                console.log(mainRoot.pressure)
                            }
                        }
                    }
            }
        }
    }
}
