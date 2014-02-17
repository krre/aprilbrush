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
import QtQuick.Controls 1.1
import QtQuick.Layouts 1.1
import "components"
import "brushlib.js" as BrushLib
import "settings.js" as Settings

ToolWindow {
    id: root
    title: "Brush Library"
    objectName: "brushLibrary"
    storage: {
        var list = Settings.defaultStorage()
        return list
    }

    function changeBrushSettings(row) {
        brushSettings.diameter = libraryModel.get(row).size
        brushSettings.opaque = libraryModel.get(row).opaque
        brushSettings.spacing = libraryModel.get(row).spacing
        brushSettings.hardness = libraryModel.get(row).hardness
//        brushSettings.roundness = libraryModel.get(row).roundness
//        brushSettings.angle = libraryModel.get(row).angle
//        brushSettings.jitter = libraryModel.get(row).jitter
    }

    Item {
        anchors.fill: parent

        VerticalList {
            anchors.fill: parent
            model: libraryModel
            onCurrentIndexChanged: changeBrushSettings(currentIndex)
            Component.onCompleted: BrushLib.loadBrushPack()
        }

        ListModel {
            id: libraryModel
        }
    }
}
