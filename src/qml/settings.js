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
                height: 200,
                color: {
                    h: 0.6,
                    s: 1.0,
                    v: 1.0
                },
                visible: true
            },

            brushSettings: {
                height: 250,
                visible: true
            },

            brushLibrary: {
                height: 200,
                visible: true
            },

            layerManager: {
                height: 200,
                visible: true
            },

            undoManager: {
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

    colorPicker.height = settings.colorPicker.height
    colorPicker.color = Utils.hsvToHsl(settings.colorPicker.color.h,
                                       settings.colorPicker.color.s,
                                       settings.colorPicker.color.v)

    brushSettings.height = settings.brushSettings.height

    brushLibrary.height = settings.brushLibrary.height

    layerManager.height = settings.layerManager.height

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
            height: colorPicker.height,
            color: {
                  h: colorPicker.h,
                  s: colorPicker.s,
                  v: colorPicker.v
            },
            visible: colorPicker.visible
        },

        brushSettings: {
            height: brushSettings.height,
            visible: brushSettings.visible
        },

        brushLibrary: {
            height: brushLibrary.height,
            visible: brushLibrary.visible
        },

        layerManager: {
            height: layerManager.height,
            visible: layerManager.visible
        },

        undoManager: {
            height: undoManager.height,
            visible: undoManager.visible
        }
    }

    coreLib.saveSettings(JSON.stringify(fileSettings, null, 4))
}
