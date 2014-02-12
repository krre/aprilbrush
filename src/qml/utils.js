/* AprilBrush - Digital Painting Software
 * Copyright (C) 2012-2013 Vladimir Zarypov <krre31@gmail.com>
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

// Add new tab
function addTab(tabName) {
    var newTabName = tabName ? tabName : qsTr("Untitled-") + (++newTabCounter)
    tabView.addTab(newTabName, tabView.tabComponent)
    tabView.currentIndex = tabView.count - 1

    if (!tabName) {
        addLayer("Background", "white")
        addLayer()
    }

    undoManager.add(new Undo.start())
}

// Delete page
function deletePage(index) {
    var layerModel = pageModel.get(index).layerModel
    if (layerModel.count > 0)
        for (var i = 0; i < layerModel.count; i++) {
            var layerId = layerModel.get(i).layerId
            imgProcessor.deletePixmap(layerId)
        }
    pageModel.remove(index)
}


// Add new layer
function addLayer(layerName, color) {
    var newLayerName = layerName ? layerName : qsTr("Layer-") + (++tabContent.newLayerCounter)
    var newColor = color ? color : "transparent"
    var newLayerId = (layerIdCounter++).toString()

    imgProcessor.addPixmap(newLayerId, imageSize, newColor)

    var insertPos = layerManager.layerView.currentIndex < 0 ? 0 : layerManager.layerView.currentIndex
    layerModel.insert(insertPos, { name: newLayerName, colorImage: newColor, enable: true, layerId: newLayerId })
    layerManager.layerView.currentIndex = insertPos
}

// Delete layer
function deleteLayer(index) {
    var layerId = layerModel.get(index).layerId
    layerModel.remove(index)
    imgProcessor.deletePixmap(layerId)
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

// Open OpenRaster file
function openOra(filePath) {
    //var layerModel = pageModel.get(currentPageIndex).layerModel
    var path = filePath.toString()
    path = polishPath(path)
    var layersList = openRaster.readAttributes(path)

    addPage(fileFromPath(path))
    for (var i = layersList.length - 1; i > -1; i-- ) {
        addLayer(layersList[i].name)
        var src = layersList[i].src
        var layerId = pageModel.get(currentPageIndex).layerModel.get(0).layerId
        openRaster.readPixmap(path, src, layerId)
    }
    currentPageItem.canvasArea.oraPath = path
    console.log("open: " + path)
}

// Save OpenRaster file with new name
function saveAsOra(filePath) {
    var path = filePath.toString()
    if (path.substr(-4) !== ".ora")
        path += ".ora"

    path = polishPath(path)

    currentPageItem.canvasArea.oraPath = path
    saveOra(path)
    pageModel.get(currentPageIndex).name = fileFromPath(path)
}

// Save OpenRaster file
function saveOra() {
    var path = currentPageItem.canvasArea.oraPath
    var layerModel = pageModel.get(currentPageIndex).layerModel
    var layerList = []
    for (var i = 0; i < layerModel.count; i++) {
        layerList.push({ "name": layerModel.get(i).name,
                         "layerId": layerModel.get(i).layerId,
                         "enable": layerModel.get(i).enable})
    }
    openRaster.write(path, imageSize, layerList)
    console.log("save: " + path)
}

// Export PNG file
function exportPng(filePath) {
    var layerModel = pageModel.get(currentPageIndex).layerModel
    var path = filePath.toString()
    if (path.substr(-4) !== ".png")
        path += ".png"
    var layerIdList = []
    for (var i = 0; i < layerModel.count; i++)
        layerIdList.push(layerModel.get(i).layerId)
    path = polishPath(path)
    imgProcessor.makePng(path, layerIdList)
    console.log("export: " + path)
}

// Pick color from canvas
function pickColor(pos) {
    var layerIdList = []
    for (var i = 0; i < layerModel.count; i++)
        layerIdList.push(layerModel.get(i).layerId)

    return imgProcessor.pickColor(pos, layerIdList)
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
    var l = (2 - s) * v
    var computedH = s * v / (l <= 1 ? l : 2 - l)
    l /= 2
    return Qt.hsla(h, computedH, l, 1)
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
