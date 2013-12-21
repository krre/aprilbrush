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
import ABLib 1.0
import "components"
import "settings.js" as Settings
import "utils.js" as Utils
import "undo.js" as Undo
import "style.js" as Style

ApplicationWindow {
    id: mainRoot
    title: "AprilBrush"

    property string version: "AprilBrush 1.1.0"
    property var palette: Style.defaultStyle()

    property int newPageCounter: 0
    property int newLayerCounter: 0
    property variant layerModel: 0

    property var settings

    property size imageSize: coreLib.screenSize()
    property bool eraserMode: false
//    property variant currentPageItem: pageManager.pagesView.currentItem
//    property int currentPageIndex: pageManager.pagesView.currentIndex
    property int layerIdCounter: 0
    property string currentLayerId

    Component.onCompleted: {
        Settings.loadSettings()
        Utils.addPage()
    }
    Component.onDestruction: Settings.saveSettings()

    menuBar: MenuBar {
        Menu {
            title: qsTr("File")
            MenuItem {
                text: qsTr("New")
                shortcut: "Ctrl+N"
                onTriggered: Utils.addPage()
            }
            MenuItem {
                text: qsTr("Open...")
                shortcut: "Ctrl+O"
                onTriggered: {
                    var component = Qt.createComponent("FileDialog.qml");
                    if (component.status === Component.Ready) {
                        var object = component.createObject(mainRoot, { mode: 0 });
                    }
                }
            }
            MenuItem {
                text: qsTr("Save")
                shortcut: "Ctrl+S"
                enabled: pageView.count > 0
            }
            MenuItem {
                text: qsTr("Save As...")
                shortcut: "Ctrl+Shift+S"
                enabled: pageView.count > 0
                onTriggered: {
                    var component = Qt.createComponent("FileDialog.qml");
                    if (component.status === Component.Ready) {
                        var object = component.createObject(mainRoot, { mode: 1 });
                    }
                }
            }
            MenuItem {
                text: qsTr("Export...")
                shortcut: "Ctrl+E"
                enabled: pageView.count > 0
                onTriggered: {
                    var component = Qt.createComponent("FileDialog.qml");
                    if (component.status === Component.Ready) {
                        var object = component.createObject(mainRoot, { mode: 2 });
                    }
                }
            }
            MenuItem {
                text: qsTr("Close")
                shortcut: "Ctrl+W"
                onTriggered: {
                    pageView.removeTab(pageView.currentIndex)
                    if (!pageView.count)
                        newPageCounter = 0
                }
                enabled: pageView.count > 0
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
            }
            MenuItem {
                text: qsTr("Redo")
                shortcut: "Ctrl+Y"
            }
        }

        Menu {
            title: qsTr("Help")
            MenuItem {
                text: qsTr("About...")
                onTriggered: {
                    var component = Qt.createComponent("About.qml");
                    if (component.status === Component.Ready) {
                        var object = component.createObject(mainRoot);
                    }
                }
            }
        }
    }

    SplitView {
        anchors.fill: parent
        orientation: Qt.Horizontal

        SplitView {
            Layout.minimumWidth: 200
            orientation: Qt.Vertical

            ColorPicker {
                id: colorPicker
                width: parent.width
                color: Utils.hsvToHsl(settings.colorPicker.color.h,
                                      settings.colorPicker.color.s,
                                      settings.colorPicker.color.v)
            }

            LayerManager {
                id: layerManager
                width: parent.width
            }

            Item {
                Layout.fillHeight: true
            }

        }

        TabView {
            id: pageView
            Layout.minimumWidth: 200
            Layout.fillWidth: true
            visible: count > 0
            onCountChanged: count > 0 ? layerModel = pageModel.get(pageView.currentIndex).layerModel : 0
        }

        SplitView {
            Layout.minimumWidth: 200
            orientation: Qt.Vertical

            BrushSettings {
                id: brushSettings
                width: parent.width
            }

            UndoManager {
                id: undoManager
                width: parent.width
            }

            BrushLibrary {
                id: brushLibrary
            }

            Item {
                Layout.fillHeight: true
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
        onPaintDone: currentPageItem.canvasArea.pathView.currentItem.update()
    }

    ImageProcessor {
        id: imgProcessor
        layerId: currentLayerId
    }

    OpenRaster {
        id: openRaster
        imageProcessor: imgProcessor
    }

    CoreLib {
        id: coreLib
    }

    ListModel {
        id: pageModel
    }

/*
    CanvasArea {
        id: canvasArea
    }
*/
}

