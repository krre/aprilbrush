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

    property string version: "1.1.0"
    property string appName: "AprilBrush"
    property var palette: Style.defaultStyle()

    property int newTabCounter: 0

    property var tabContent: tabView.count > 0 ? tabView.getTab(tabView.currentIndex).item : 0
    property var layerModel: tabView.count > 0 ? tabContent.layerModel : []
    property var undoModel: tabView.count > 0 ? tabContent.undoModel : []

    property var settings

    property size imageSize
    property bool eraserMode: false
    property int layerIdCounter: 0
    property string currentLayerId

    Component.onCompleted: {
        imageSize = Qt.size(Screen.width, Screen.height)
        Settings.loadSettings()
        Utils.addTab()
    }
    Component.onDestruction: Settings.saveSettings()

    TabView {
        id: tabView
        property alias tabComponent: tabComponent
        anchors.fill: parent
        visible: count > 0
        focus: true

        Keys.onPressed: {
            event.accepted = true;
            if (event.key === Qt.Key_Tab) {
                dock.visible = !dock.visible
            }
        }

        Component {
            id: tabComponent

            Item {
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
}

