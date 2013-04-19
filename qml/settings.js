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

// Load settings
function loadSettings() {
    var fileSettings = coreLib.loadSettings()
    if (fileSettings)
        settings = JSON.parse(fileSettings)
    else
        // Default settings
        settings = {
            mainWindow: {
                width: 1000,
                height: 600
            },

            colorPicker: {
                position: {
                    x: 20,
                    y: 50,
                    z: 2
                },
                size: {
                    width: 200,
                    height: 200
                },
                color: {
                    h: 0.6,
                    s: 1.0,
                    v: 1.0
                },
                visible: true
            },

            brushSettings: {
                position: {
                    x: 780,
                    y: 50,
                    z: 3
                },
                size: {
                    width: 200,
                    height: 250
                },
                visible: true
            },

            brushLibrary: {
                position: {
                    x: 570,
                    y: 50,
                    z: 4
                },
                size: {
                    width: 200,
                    height: 200
                },
                visible: true
            },

            layerManager: {
                position: {
                    x: 20,
                    y: 300,
                    z: 5
                },
                size: {
                    width: 200,
                    height: 200
                },
                visible: true
            },

            undoManager: {
                position: {
                    x: 780,
                    y: 310,
                    z: 6
                },
                size: {
                    width: 200,
                    height: 200
                },
                visible: true
            },
        }
}

// Save settings
function saveSettings() {
    var fileSettings = {
        mainWindow: {
            width: main.width,
            height: main.height
        },

        colorPicker: {
            position: {
                x: colorPicker.x,
                y: colorPicker.y,
                z: colorPicker.z
            },
            size: {
                width: colorPicker.width,
                height: colorPicker.height
            },
            color: {
              h: colorPicker.h,
              s: colorPicker.s,
              v: colorPicker.v
            },
            visible: colorPicker.visible
        },

        brushSettings: {
            position: {
                x: brushSettings.x,
                y: brushSettings.y,
                z: brushSettings.z
            },
            size: {
                width: brushSettings.width,
                height: brushSettings.height
            },
            visible: brushSettings.visible
        },

        brushLibrary: {
            position: {
                x: brushLibrary.x,
                y: brushLibrary.y,
                z: brushLibrary.z
            },
            size: {
                width: brushLibrary.width,
                height: brushLibrary.height
            },
            visible: brushLibrary.visible
        },

        layerManager: {
            position: {
                x: layerManagerPos.x,
                y: layerManagerPos.y,
                z: layerManagerPos.z
            },
            size: {
                width: layerManagerSize.width,
                height: layerManagerSize.height
            },
            visible: layerManagerVisible
        },

        undoManager: {
            position: {
                x: undoManagerPos.x,
                y: undoManagerPos.y,
                z: undoManagerPos.z
            },
            size: {
                width: undoManagerSize.width,
                height: undoManagerSize.height
            },
            visible: undoManagerVisible
        }
    }

    coreLib.saveSettings(JSON.stringify(fileSettings, null, 4))
}
