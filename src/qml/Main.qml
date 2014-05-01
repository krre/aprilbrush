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
import "main"

ApplicationWindow {
    id: mainRoot
    title: "AprilBrush"
    property string version: "0.2"
    property size imageSize: Qt.size(Screen.width, Screen.height)
    property CanvasArea currentTab: tabView.count > 0 ? tabView.getTab(tabView.currentIndex).item : null
    property ListModel layerModel: currentTab ? currentTab.layerModel : null
    property real pressure: 0
    property alias sysPalette: sysPalette

    width: 1000
    height: 600
    visible: true

    menuBar: MenuBarContent {}
    toolBar: ToolBarContent { id: toolBar }
    statusBar: StatusBarContent { id: statusBar }

    Component.onCompleted: {
        Settings.loadSettings(mainRoot)
        actions.newAction.trigger()
    }

    onClosing: Settings.saveSettings(mainRoot)

    SystemPalette {
        id: sysPalette
        colorGroup: SystemPalette.Active
    }

    Connections {
        target: PointerEater
        onPressure: mainRoot.pressure = pressure
        onPressed: type == 0 ? mainRoot.pressure = 1 : mainRoot.pressure = 0
    }

    Actions { id: actions}
    CoreLib { id: coreLib }
    FileDialog { id: fileDialog }
    About { id: about }

    TabView {
        id: tabView
        anchors.fill: parent
    }

    ColorPicker {
        id: colorPicker
        relativeX: 20
        relativeY: 100
        onColorChanged: brushSettings.dab.requestPaint()
    }

    LayerManager {
        id: layerManager
        relativeX: 20
        relativeY: 340
    }

    BrushSettings {
        id: brushSettings
        relativeX: mainRoot.width - width - 30
        relativeY: 100
        onSettingsChanged: dab.requestPaint()
    }

    BrushLibrary {
        id: brushLibrary
        relativeX: mainRoot.width - width - 30
        relativeY: 340
    }

    Component {
        id: canvasArea
        CanvasArea {}
    }

    Item {
        property alias mainX: mainRoot.x
        property alias mainY: mainRoot.y
        property alias mainWidth: mainRoot.width
        property alias mainHeight: mainRoot.height
        property var storage: ["mainWidth", "mainHeight", "mainX", "mainY"]
        objectName: "commonStorage"
    }
}
