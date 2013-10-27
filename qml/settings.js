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

.import "utils.js" as Utils

function loadSettings() {
    var fileSettings = coreLib.loadSettings()
    if (!fileSettings) {
        // Default settings
        settings = {
            mainWindow: {
                width: 1000,
                height: 600,
                x: 100,
                y: 100
            },

            colorPicker: {
                x: 20,
                y: 50,
                width: 200,
                height: 200,
                color: {
                    h: 0.6,
                    s: 1.0,
                    v: 1.0
                },
                visible: true
            },

            brushSettings: {
                x: 780,
                y: 50,
                width: 200,
                height: 250,
                visible: true
            },

            brushLibrary: {
                x: 570,
                y: 50,
                width: 200,
                height: 200,
                visible: true
            },

            layerManager: {
                x: 20,
                y: 300,
                width: 200,
                height: 200,
                visible: true
            },

            undoManager: {
                x: 780,
                y: 310,
                width: 200,
                height: 200,
                visible: true
            },
        }
    }
    else {
        settings = JSON.parse(fileSettings)
    }

    mainWindow.x = settings.mainWindow.x
    mainWindow.y = settings.mainWindow.y
    mainWindow.width = settings.mainWindow.width
    mainWindow.height = settings.mainWindow.height

    colorPicker.x = settings.colorPicker.x
    colorPicker.y = settings.colorPicker.y
    colorPicker.width = settings.colorPicker.width
    colorPicker.height = settings.colorPicker.height
    colorPicker.color = Utils.hsvToHsl(settings.colorPicker.color.h,
                                       settings.colorPicker.color.s,
                                       settings.colorPicker.color.v)

    brushSettings.x = settings.brushSettings.x
    brushSettings.y = settings.brushSettings.y
    brushSettings.width = settings.brushSettings.width
    brushSettings.height = settings.brushSettings.height

    brushLibrary.x = settings.brushLibrary.x
    brushLibrary.y = settings.brushLibrary.y
    brushLibrary.width = settings.brushLibrary.width
    brushLibrary.height = settings.brushLibrary.height

    layerManager.x = settings.layerManager.x
    layerManager.y = settings.layerManager.y
    layerManager.width = settings.layerManager.width
    layerManager.height = settings.layerManager.height

    undoManager.x = settings.undoManager.x
    undoManager.y = settings.undoManager.y
    undoManager.width = settings.undoManager.width
    undoManager.height = settings.undoManager.height
}

function saveSettings() {
    var fileSettings = {
        mainWindow: {
            width: mainWindow.width,
            height: mainWindow.height,
            x: mainWindow.x,
            y: mainWindow.y
        },

        colorPicker: {
            x: colorPicker.x,
            y: colorPicker.y,
            width: colorPicker.width,
            height: colorPicker.height,
            color: {
                  h: colorPicker.h,
                  s: colorPicker.s,
                  v: colorPicker.v
            },
            visible: colorPicker.visible
        },

        brushSettings: {
            x: brushSettings.x,
            y: brushSettings.y,
            width: brushSettings.width,
            height: brushSettings.height,
            visible: brushSettings.visible
        },

        brushLibrary: {
            x: brushLibrary.x,
            y: brushLibrary.y,
            width: brushLibrary.width,
            height: brushLibrary.height,
            visible: brushLibrary.visible
        },

        layerManager: {
            x: layerManager.x,
            y: layerManager.y,
            width: layerManager.width,
            height: layerManager.height,
            visible: layerManager.visible
        },

        undoManager: {
            x: undoManager.x,
            y: undoManager.y,
            width: undoManager.width,
            height: undoManager.height,
            visible: undoManager.visible
        }
    }

    coreLib.saveSettings(JSON.stringify(fileSettings, null, 4))
}
