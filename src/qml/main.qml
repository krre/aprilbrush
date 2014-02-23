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

Rectangle {
    id: mainRoot
    property real pressure: 0
    property var palette: Style.defaultStyle()
    property size imageSize: Qt.size(Screen.width, Screen.height)
    property int currentPageIndex: pageManager.pageView.currentIndex
    property int currentLayerIndex: layerManager.layerView.currentIndex
    property var layerModel: currentPageIndex >= 0 ? mainModel.get(currentPageIndex).layerModel : []

    width: 1000
    height: 600
    color: "lightgray"

    Component.onCompleted: {
        Settings.loadSettings()
    }

    Component.onDestruction: Settings.saveSettings()

    Connections {
        target: PointerEater
        onPressure: mainRoot.pressure = pressure
        onPressed: type == 0 ? mainRoot.pressure = 1 : mainRoot.pressure = 0
    }

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

    ListModel {
        id: mainModel
    }

    ListView {
        id: canvasView
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

    ColorPicker {
        id: colorPicker
        x: 25
        y: 120
        onColorChanged: brushSettings.dab.requestPaint()
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

    CoreLib {
        id: coreLib
    }
}
