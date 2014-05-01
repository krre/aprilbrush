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
    property size imageSize: Qt.size(Screen.width, Screen.height)
    property Tab currentTab: tabView.count > 0 ? tabView.getTab(tabView.currentIndex) : null

    /*
    property real pressure: 0
    property var palette: Style.defaultStyle()
    property int currentPageIndex: pageManager.pageView.currentIndex
    property int currentLayerIndex: layerManager.layerView.currentIndex
    property var layerModel: currentPageIndex >= 0 ? mainModel.get(currentPageIndex).layerModel : []
*/

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

    Actions { id: actions}
    CoreLib { id: coreLib }
    FileDialog { id: fileDialog }

    TabView {
        id: tabView
        anchors.fill: parent
//        frameVisible: false
    }

    ColorPicker {
        id: colorPicker
        x: { return 20 + mainRoot.x }
        y: { return 100 + mainRoot.y }
        onColorChanged: brushSettings.dab.requestPaint()
    }

    LayerManager {
        id: layerManager
        x: { return 20 + mainRoot.x }
        y: { return 340 + mainRoot.y }
    }

    BrushSettings {
        id: brushSettings
        x: { return mainRoot.width - width - 20 }
        y: { return 100 + mainRoot.y }
        onSettingsChanged: dab.requestPaint()
    }

    BrushLibrary {
        id: brushLibrary
        x: { return mainRoot.width - width - 20 }
        y: { return 340 + mainRoot.y }
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
