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

.import "undo.js" as Undo

// Open OpenRaster file
function openOra(filePath) {
    var path = filePath.toString()
    path = polishPath(path)

    tabView.addTab(fileFromPath(path), canvasArea)
    tabView.currentIndex = tabView.count - 1
    var layersList = coreLib.readOra(path)

    for (var i = layersList.length - 1; i > -1; i-- ) {
        layerManager.addLayer(layersList[i].name, "transparent")
        var image = layersList[i].image
        var canvas = layerModel.get(0).canvas
        canvas.loadImage(image)

        var j = layersList.length - 1
        canvas.onImageLoaded.connect(function() {
            if (j > -1) {
                var canvas = layerModel.get(j).canvas
                var image = layersList[j].image
                var context = canvas.getContext("2d")
                context.drawImage(image, 0, 0)
                canvas.requestPaint()
                j--
            }
        })
    }
    currentTab.oraPath = path
    undoManager.add(new Undo.start())
    console.log("open: " + path)
}

// Save OpenRaster file with new name
function saveAsOra(filePath) {
    var path = filePath.toString()
    if (path.substr(-4) !== ".ora") {
        path += ".ora"
    }
    path = polishPath(path)
    currentTab.oraPath = path
    tabView.getTab(tabView.currentIndex).title = fileFromPath(path)
    saveOra()
}

// Save OpenRaster file
function saveOra() {
    var path = currentTab.oraPath
    var layerList = []
    for (var i = 0; i < layerModel.count; i++) {
        var image = layerModel.get(i).canvas.toDataURL()
        image = image.substring(22, image.length) // cutting first block "data:image/png;base64,"
        var visible = layerModel.get(i).layerVisible
        layerList.push({ "name": layerModel.get(i).name,
                         "visible": visible,
                         "image": image
                       })
    }
    coreLib.writeOra(path, imageSize, layerList)
    console.log("save: " + path)
}

// Export PNG file
function exportPng(filePath) {
    var path = filePath.toString()
    if (path.substr(-4) !== ".png") {
        path += ".png"
    }
    path = polishPath(path)

    var finalCanvas = exportCanvas.createObject(currentTab)
    finalCanvas.onFinished.connect(function() {
        finalCanvas.save(path)
        finalCanvas.destroy()
        console.log("export: " + path)
    })
}

// Pick color from canvas
function pickColor(pos) {
    var finalCanvas = exportCanvas.createObject(currentTab)
    finalCanvas.onFinished.connect(function() {
        var ctx = finalCanvas.getContext("2d")
        var p = ctx.getImageData(pos.x, pos.y, 1, 1).data
        var hex = "#" + ("000000" + rgbToHex(p[0], p[1], p[2])).slice(-6);
        colorPicker.color = hex
        finalCanvas.destroy()
    })
}

// Add prefix zero to number
function zeroFill(number, width)
{
    width -= number.toString().length;
    if (width > 0)
    {
        return new Array(width + (/\./.test(number) ? 2 : 1)).join('0') + number;
    }
    return number + ""; // always return a string
}

// Convert HSV to HSL
function hsvToHsl(h, s, v) {
    var l = (2 - s) * v / 2
    var computedS = s * v / (1 - Math.abs(2 * l - 1))
    return Qt.hsla(h, computedS, l, 1)
}

// Convert RGB to HSV
function rgbToHsv(color) {
    var r = color.r
    var g = color.g
    var b = color.b

    var minRGB = Math.min(r, Math.min(g, b))
    var maxRGB = Math.max(r, Math.max(g, b))

     // Black-gray-white
     if (minRGB == maxRGB) {
        var computedV = minRGB
        return { h: 0, s: 0, v: computedV }
     }

     // Colors other than black-gray-white
     var d = (r === minRGB) ? g - b : ((b === minRGB) ? r - g : b - r)
     var h = (r === minRGB) ? 3 : ((b === minRGB) ? 1 : 5)
     var computedH = (h - d / (maxRGB - minRGB)) / 6
     var computedS = (maxRGB - minRGB) / maxRGB
     computedV = maxRGB

     return { h: computedH, s: computedS, v: computedV }
}

// Convert RGB to HEX
function rgbToHex(r, g, b) {
    if (r > 255 || g > 255 || b > 255)
        throw "Invalid color component";
    return ((r << 16) | (g << 8) | b).toString(16);
}

// Convert HSV to RGB
function hsvToRgb(h, s, v) {
    var r, g, b, i, f, p, q, t;
    if (h && s === undefined && v === undefined) {
        s = h.s; v = h.v; h = h.h;
    }
    i = Math.floor(h * 6);
    f = h * 6 - i;
    p = v * (1 - s);
    q = v * (1 - f * s);
    t = v * (1 - (1 - f) * s);
    switch (i % 6) {
        case 0: r = v; g = t; b = p; break;
        case 1: r = q; g = v; b = p; break;
        case 2: r = p; g = v; b = t; break;
        case 3: r = p; g = q; b = v; break;
        case 4: r = t; g = p; b = v; break;
        case 5: r = v; g = p; b = q; break;
    }
    return Qt.rgba(r, g, b, 1)
}

function polishPath(path) {
    var re = new RegExp("\/{2,}", "g")
    path = path.replace(re, "/")
    path = path.replace("file:", "")
    re = new RegExp("^\/.:")
    if (re.test(path))
        path = path.substring(1)

    return path
}

// Get filename from path
function fileFromPath(path) {
    return path.substr(path.lastIndexOf("/") + 1)
}

// Get folder from path
function folderFromPath(path) {
    return path.replace(/^.*[\\\/]/, '')
}

function createDynamicObject(parent, name, item) {
    var component = Qt.createComponent(name);
    var errorMessage = component.errorString()
    if (errorMessage !== "") {
        console.log("Error loading component " + name + ":", errorMessage);
    }
    else {
        if (item) {
            return component.createObject(parent, item)
        } else {
            return component.createObject(parent)
        }
    }
}
