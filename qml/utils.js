// Add new page
function addPage(pageName) {
    var newPageName
    if (pageName)
        newPageName = pageName
    else {
        // Calculate next number page
        var maxNumPage = 0;
        for (var page = 0; page < pageModel.count; page++) {
            var numPage = parseInt(pageModel.get(page).name.substring(6), 10)
            if (numPage > maxNumPage) maxNumPage = numPage
        }
        maxNumPage++
        var numNextPage = zeroFill(maxNumPage, 3)
        newPageName = "Page-" + numNextPage
    }

    pageModel.append({name: newPageName, layerModel: [], undoModel: [] })
    pageManager.pagesView.currentIndex = pageModel.count - 1

    if (!pageName) {
        addLayer("Background", "white")
        addLayer()
    }

    //undoManager.add(new Undo.start())
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
    var layerModel = pageModel.get(currentPageIndex).layerModel
    var newLayerName
    if (layerName)
        newLayerName = layerName
    else {
        if (layerModel.count) {
            // Calculate next number layer
            var maxNumLayer = 0;
            for (var layer = 0; layer < layerModel.count; layer++) {
                var numLayer = parseInt(layerModel.get(layer).name.substring(6), 10)
                if (numLayer > maxNumLayer) maxNumLayer = numLayer
            }
            maxNumLayer++
            var numNextLayer = zeroFill(maxNumLayer, 3)
            newLayerName = "Layer-" + numNextLayer
        }
        else
            newLayerName = "Layer-001"
    }

    var newColor
    if (color)
        newColor = color
    else
        newColor = "transparent"

    var newLayerId = layerIdCounter++
    newLayerId = newLayerId.toString()
    imgProcessor.addPixmap(newLayerId, imageSize, newColor)
    layerModel.append({ name: newLayerName, colorImage: newColor, enable: true, layerId: newLayerId })
    // Set new layer as current
    if (layerModel.count > 1) {
        var selectedLayer = currentPageItem.layerManager.currentLayerIndex
        layerModel.move(layerModel.count - 1, selectedLayer, 1)
        currentPageItem.layerManager.currentLayerIndex = selectedLayer
    }
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
function openOra() {
    //var layerModel = pageModel.get(currentPageIndex).layerModel
    var path = fileDialog.currentFilePath
    path = polishPath(path)
    var layersList = openRaster.readAttributes(path)

    addPage(fileDialog.currentFileName)
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
function saveAsOra() {
    var path = fileDialog.currentFilePath
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
function exportPng() {
    var layerModel = pageModel.get(currentPageIndex).layerModel
    var path = fileDialog.currentFilePath
    if (path.substr(-4) !== ".png")
        path += ".png"
    var layerIdList = []
    for (var i = 0; i < layerModel.count; i++)
        layerIdList.push(layerModel.get(i).layerId)
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
