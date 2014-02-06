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
import QtQuick.Dialogs 1.0
import QtQuick.Controls 1.0
import QtQuick.Layouts 1.1
import QtQuick.Window 2.0
import ABLib 1.0
import "components"
import "settings.js" as Settings
import "utils.js" as Utils
import "undo.js" as Undo
import "style.js" as Style

ApplicationWindow {
    id: mainRoot
    title: appName
    property real pressure: 0

    property string version: "0.2.0"
    property string appName: "AprilBrush"
    property var palette: Style.defaultStyle()

    property int newTabCounter: 0

//    property var tabContent: tabView.count > 0 ? tabView.getTab(tabView.currentIndex).item : 0
//    property var layerModel: tabView.count > 0 ? tabContent.layerModel : []
//    property var undoModel: tabView.count > 0 ? tabContent.undoModel : []

    property var settings

    property size imageSize: Qt.size(Screen.width, Screen.height)
    property bool eraserMode: false
    property int layerIdCounter: 0
    property string currentLayerId

    Component.onCompleted: {
//        Settings.loadSettings()
//        Utils.addTab()
        width = 1000
        height = 600
    }
//    Component.onDestruction: Settings.saveSettings()

    Connections {
        target: PointerEater
        onPressure: mainRoot.pressure = pressure
        onPressed: type == 0 ? mainRoot.pressure = 1 : mainRoot.pressure = 0
    }

    Canvas {
        id: canvas
        width: imageSize.width
        height: imageSize.height
        anchors.centerIn: parent
        antialiasing: true

        Component.onCompleted: requestPaint()

        property color fillStyle: "#ffffff"

        onPaint: {
            var ctx = canvas.getContext("2d")
            ctx.save()
            ctx.fillStyle = canvas.fillStyle
            ctx.fillRect(0, 0, width, height)
            ctx.restore();
        }

        MouseArea {
            anchors.fill: parent
            onPositionChanged: { canvas.drawDab(mouseX, mouseY) }
        }

        function drawDab(x, y) {
            var dabCanvas = dab.getContext("2d").getImageData(0, 0, dab.width, dab.height)
            var ctx = canvas.getContext("2d")
            ctx.save()
            ctx.drawImage(dabCanvas, x, y)
            ctx.restore()
            markDirty(x, y, dab.width, dab.height)
        }
    }

    Canvas {
        id: dab
        width: 20
        height: 20
        visible: false
        antialiasing: true

        onPaint: {
            var ctx = dab.getContext("2d")
            ctx.save()
            ctx.fillStyle = Qt.rgba(0.5, 0, 0, 0.5)
            ctx.fillRect(0, 0, width, height)
            ctx.restore();
        }
    }


    /*

    TabView {
        id: tabView
        property alias tabComponent: tabComponent
        anchors.fill: parent
        visible: count > 0
        focus: true

        onCurrentIndexChanged: tabContent.canvasArea.pathView.currentItem.update()

        Keys.onPressed: {
            event.accepted = true;
            if (event.key === Qt.Key_Tab) {
                if (!event.isAutoRepeat) {
                    dock.visible = !dock.visible
                }
            }
        }

        Component {
            id: tabComponent

            Item {
                property alias canvasArea: canvasArea
                property alias layerModel: layerModel
                property alias undoModel: undoModel
                property int newLayerCounter: 0

                CanvasArea {
                    id: canvasArea
                }

                ListModel {
                    id: layerModel
                }

                ListModel {
                    id: undoModel
                }
            }
        }
    }

    Item {
        id: dock
        width: 650
        height: 600
        visible: false
        anchors.centerIn: parent

        ColumnLayout {
            anchors.left: parent.left
            width: 200
            height: parent.height
            spacing: 0

            LayerManager {
                id: layerManager
                Layout.fillHeight: true
            }

            BrushSettings {
                id: brushSettings
                Layout.fillHeight: true
            }
        }

        ColorPicker {
            id: colorPicker
            anchors.centerIn: parent
            color: Utils.hsvToHsl(settings.colorPicker.color.h,
                                  settings.colorPicker.color.s,
                                  settings.colorPicker.color.v)
        }

        ColumnLayout {
            anchors.right: parent.right
            width: 200
            height: parent.height
            spacing: 0

            UndoManager {
                id: undoManager
                Layout.fillHeight: true
            }

            BrushLibrary {
                id: brushLibrary
                Layout.fillHeight: true
            }
        }
    }

    menuBar: MenuBar {
        Menu {
            title: qsTr("File")
            MenuItem {
                text: qsTr("New")
                shortcut: "Ctrl+N"
                onTriggered: Utils.addTab()
            }
            MenuItem {
                text: qsTr("Open...")
                shortcut: "Ctrl+O"
                onTriggered: Utils.createDynamicObject(mainRoot, "FileDialog.qml", { mode: 0 })
            }
            MenuItem {
                text: qsTr("Save")
                shortcut: "Ctrl+S"
                enabled: tabView.count > 0
            }
            MenuItem {
                text: qsTr("Save As...")
                shortcut: "Ctrl+Shift+S"
                enabled: tabView.count > 0
                onTriggered: Utils.createDynamicObject(mainRoot, "FileDialog.qml", { mode: 1 })
            }
            MenuItem {
                text: qsTr("Export...")
                shortcut: "Ctrl+E"
                enabled: tabView.count > 0
                onTriggered: Utils.createDynamicObject(mainRoot, "FileDialog.qml", { mode: 2 })
            }
            MenuItem {
                text: qsTr("Close")
                shortcut: "Ctrl+W"
                onTriggered: {
                    tabView.removeTab(tabView.currentIndex)
                    if (!tabView.count)
                        newTabCounter = 0
                }
                enabled: tabView.count > 0
            }
            MenuSeparator { }
            MenuItem {
                text: qsTr("Quit")
                shortcut: "Ctrl+Q"
                onTriggered: mainRoot.close()
            }
        }

        Menu {
            title: qsTr("Edit")
            MenuItem {
                text: qsTr("Undo")
                shortcut: "Ctrl+Z"
                enabled: (tabView.count > 0) && (undoManager.undoView.currentIndex > 0)
                onTriggered: undoManager.undoView.listView.decrementCurrentIndex()
            }
            MenuItem {
                text: qsTr("Redo")
                shortcut: "Ctrl+Y"
                enabled: (tabView.count > 0) && (undoManager.undoView.currentIndex < undoManager.undoView.listView.count - 1)
                onTriggered: undoManager.undoView.listView.incrementCurrentIndex()
            }
        }

        Menu {
            title: qsTr("Canvas")
            MenuItem {
                text: qsTr("Clear")
                onTriggered: {
                    undoManager.add(new Undo.clear())
                    brushEngine.clear()
                    tabContent.canvasArea.pathView.currentItem.update()
                }
                shortcut: "Delete"
                enabled: tabView.count > 0
            }

            MenuItem {
                text: qsTr("Fill Color")
                onTriggered: {
                    undoManager.add(new Undo.fillColor())
                }
                shortcut: "F"
                enabled: tabView.count > 0
            }
        }

        Menu {
            title: qsTr("Brushes")

            MenuItem {
                text: qsTr("Brush")
                onTriggered: {
                    eraserMode = false
                }
                shortcut: "B"
                enabled: tabView.count > 0
            }

            MenuItem {
                text: qsTr("Eraser")
                onTriggered: {
                    eraserMode = true
                }
                shortcut: "E"
                enabled: tabView.count > 0
            }
        }



        Menu {
            title: qsTr("Help")
            MenuItem {
                text: qsTr("About...")
                onTriggered: Utils.createDynamicObject(mainRoot, "About.qml")
            }
        }
    }

    BrushEngine {
        id: brushEngine
        color: colorPicker.color
        size: brushSettings.size.value
        spacing: brushSettings.spacing.value
        hardness: brushSettings.hardness.value
        opacity: brushSettings.opaque.value
        roundness: brushSettings.roundness.value
        angle: brushSettings.angle.value
        jitter: brushSettings.jitter.value
        eraser: eraserMode
        layerId: currentLayerId
        imageProcessor: imgProcessor
        onPaintDone: tabContent.canvasArea.pathView.currentItem.update()
    }

    ImageProcessor {
        id: imgProcessor
        layerId: currentLayerId
    }

    OpenRaster {
        id: openRaster
        imageProcessor: imgProcessor
    }
    */

    CoreLib {
        id: coreLib
    }



/*
    ShaderEffect {
        x: 100
        y: 330
        width: 400
        property color c3: Qt.rgba(0.0, 1.0, 0.0, 1.0)
        rotation: -90
        height: width * Math.sqrt(3) / 2
        fragmentShader: "
            varying highp vec2 qt_TexCoord0;
            uniform vec4 c3;
            void main(void)
            {
                lowp vec4 c1 = vec4( 0.0, 0.0, 0.0, 1.0 );
                lowp vec4 c0 = vec4( 0.0, 0.0, 0.0, 0.0 );
                lowp vec4 c2 = vec4( 1.0, 1.0, 1.0, 1.0 );
                lowp vec4 mix1 = mix(c0, c1, qt_TexCoord0.y);
                lowp vec4 mix2 = mix(c2, c3, qt_TexCoord0.x);
                gl_FragColor = mix1 + mix2 * (1.0 - mix1[3]);
            }"

        vertexShader: "
               uniform highp mat4 qt_Matrix;
               attribute highp vec4 qt_Vertex;
               attribute highp vec2 qt_MultiTexCoord0;
               varying highp vec2 qt_TexCoord0;
               uniform highp float width;
               void main() {
                   highp vec4 pos = qt_Vertex;
                   highp float d = .5 * smoothstep(0., 1., qt_MultiTexCoord0.y);
                   pos.x = width * mix(d, 1.0 - d, qt_MultiTexCoord0.x);
                   gl_Position = qt_Matrix * pos;
                   qt_TexCoord0 = qt_MultiTexCoord0;
               }"
    }
    */
}

