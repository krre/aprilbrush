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

import QtQuick 2.2
import QtQuick.Dialogs 1.1
import QtQuick.Controls 1.1
import QtQuick.Layouts 1.1
import QtQuick.Window 2.0
import QtQuick.Controls.Styles 1.1
import ABLib 1.0
import "settings.js" as Settings
/*
import "components"
import "settings.js" as Settings
import "utils.js" as Utils
import "undo.js" as Undo
import "style.js" as Style
*/

ApplicationWindow {
    id: mainRoot
    title: "AprilBrush"

    /*
    property real pressure: 0
    property var palette: Style.defaultStyle()
    property size imageSize: Qt.size(Screen.width, Screen.height)
    property int currentPageIndex: pageManager.pageView.currentIndex
    property int currentLayerIndex: layerManager.layerView.currentIndex
    property var layerModel: currentPageIndex >= 0 ? mainModel.get(currentPageIndex).layerModel : []
*/

    width: 1000
    height: 600
    visible: true

    Component.onCompleted: {
        x = (Screen.width - mainRoot.width) / 2
        y = (Screen.height - mainRoot.height) / 2
        Settings.loadSettings(mainRoot)
        newAction.trigger()
    }

    Component.onDestruction: Settings.saveSettings(mainRoot)

    /*
    Connections {
        target: PointerEater
        onPressure: mainRoot.pressure = pressure
        onPressed: type == 0 ? mainRoot.pressure = 1 : mainRoot.pressure = 0
    }
    */

    /*
    Keys.onSpacePressed: flickable.interactive = !flickable.interactive
    Keys.onPressed: {
        if (event.key === Qt.Key_Plus) {
            canvas.scale *= 1.1
        } else if (event.key === Qt.Key_Minus) {
            canvas.scale /= 1.1
        } else if (event.key === Qt.Key_0) {
            canvas.scale = 1
        }
    }
    */

    menuBar: MenuBar {
        Menu {
            title: qsTr("File")

            MenuItem { action: newAction }
            MenuItem { action: openAction }
            MenuItem { action: saveAction }
            MenuItem { action: saveAsAction }
            MenuSeparator {}
            MenuItem { action: closeAction }
            MenuItem { action: closeAllAction }
            MenuItem { action: closeOthersAction }
            MenuSeparator {}
            MenuItem { action: quitAction }
        }

        Menu {
            title: qsTr("Edit")
        }

        Menu {
            title: qsTr("View")

            MenuItem {
                text: qsTr("Tool Bar")
                checkable: true
                checked: true
                onTriggered: toolBar.visible = !toolBar.visible
            }

            MenuItem {
                text: qsTr("Status Bar")
                checkable: true
                checked: true
                onTriggered: statusBar.visible = !statusBar.visible
            }

            MenuItem {
                text: colorPicker.title
                checkable: true
                checked: colorPicker.visible
                onTriggered: colorPicker.visible = !colorPicker.visible
            }
        }

        Menu {
            title: qsTr("Help")

            MenuItem {
                text: qsTr("About...")
                onTriggered: print("about")
            }
        }
    }

    toolBar: ToolBar {
        id: toolBar

        RowLayout {
            ToolButton { action: newAction }
            ToolButton { action: openAction }
            ToolButton { action: saveAction }
        }
    }

    statusBar: StatusBar {
        id: statusBar
    }

    Action {
        id: newAction
        text: qsTr("New")
        shortcut: StandardKey.New
        onTriggered: {
            tabView.addTab("Untitled " + (tabView.count + 1))
            tabView.currentIndex = tabView.count - 1
        }
        tooltip: "New an Image"
    }

    Action {
        id: openAction
        text: qsTr("Open")
        shortcut: StandardKey.Open
        onTriggered: fileDialog.open()
        tooltip: "Open an Image"
    }

    Action {
        id: saveAction
        text: qsTr("Save")
        shortcut: StandardKey.Save
        onTriggered: print("save")
        tooltip: "Save an Image"
    }

    Action {
        id: saveAsAction
        text: qsTr("Save As...")
        shortcut: StandardKey.SaveAs
        onTriggered: print("save as")
        tooltip: "Save as an Image"
    }

    Action {
        id: closeAction
        text: qsTr("Close")
        shortcut: StandardKey.Close
        onTriggered: tabView.removeTab(tabView.currentIndex)
        tooltip: "Close as an Image"
        enabled: tabView.count > 0
    }

    Action {
        id: closeAllAction
        text: qsTr("Close All")
        onTriggered: {
            while (tabView.count) {
                tabView.removeTab(0)
            }
        }
        tooltip: "Close all Images"
        enabled: tabView.count > 0
    }

    Action {
        id: closeOthersAction
        text: qsTr("Close Others")
        onTriggered: {
            var currentTab = tabView.getTab(tabView.currentIndex)
            var i = 0
            while (tabView.count > 1) {
                var tab = tabView.getTab(i)
                if (tab !== currentTab) {
                    tabView.removeTab(i)
                } else {
                    i++
                }
            }
        }
        tooltip: "Close others Images"
        enabled: tabView.count > 1
    }

    Action {
        id: quitAction
        text: qsTr("Quit")
        shortcut: StandardKey.Quit
        onTriggered: Qt.quit()
        tooltip: "Quit"
    }

    CoreLib {
        id: coreLib
    }

    FileDialog {
        id: fileDialog
    }

    TabView {
        id: tabView
        anchors.fill: parent
//        frameVisible: false
    }

    ColorPicker {
        id: colorPicker
//        onColorChanged: brushSettings.dab.requestPaint()
        Component.onCompleted: {
            x = mainRoot.x + 25
            y = mainRoot.y + 120
        }
    }

    /*

    ListModel {
        id: mainModel
    }

    ListView {
        id: pageCanvasView
        anchors.fill: parent
        model: mainModel
        currentIndex: currentPageIndex
        spacing: -imageSize.width
        orientation: ListView.Horizontal
        interactive: false
        delegate: CanvasArea {}
    }

    Column {
        width: parent.width
        spacing: 0

        PageManager {
            id: pageManager
            width: parent.width
        }

        TopBar {
            id: topBar
            property var storage: ["visible"]
            objectName: "topBar"
            width: parent.width
        }

    }

    BrushSettings {
        id: brushSettings
        x: 772
        y: 120
        onSettingsChanged: dab.requestPaint()
    }

    LayerManager {
        id: layerManager
        x: 25
        y: 375
    }

    BrushLibrary {
        id: brushLibrary
        x: 780
        y: 375
    }

    Item {
        property alias mainWidth: mainRoot.width
        property alias mainHeight: mainRoot.height
        property var storage: ["mainWidth", "mainHeight"]
        objectName: "commonStorage"
    }


    */
}
