// Add new page
function addPage(pageName) {
    var newPageName
    if (pageName)
        newPageName = pageName
    else {
        // Calculate next number page
        var maxNumPage = 0;
        for (var page = 0; page < pagesModel.count; page++) {
            var numPage = parseInt(pagesModel.get(page).name.substring(6), 10)
            if (numPage > maxNumPage) maxNumPage = numPage
        }
        maxNumPage++
        var numNextPage = zeroFill(maxNumPage, 3)
        newPageName = "Page-" + numNextPage
    }

    pagesModel.append({name: newPageName, layerModel: [], undoSet: [] })
    pageManager.pagesView.currentIndex = pagesModel.count - 1

    if (!pageName) {
        addLayer("Background", "white")
        addLayer()
    }
}

// Delete page
function deletePage(index) {
    var layerModel = pagesModel.get(index).layerModel
    if (layerModel.count > 0)
        for (var i = 0; i < layerModel.count; i++) {
            var id = layerModel.get(i).layerId
            imgProcessor.deletePixmap(id)
        }
    pagesModel.remove(index)
}


// Add new layer
function addLayer(layerName, color) {
    var newLayerName
    var layerModel = pagesModel.get(currentPageIndex).layerModel
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
    var id = pagesModel.get(currentPageIndex).layerModel.get(index).layerId
    pagesModel.get(currentPageIndex).layerModel.remove(index)
    imgProcessor.deletePixmap(id)
}

// Open OpenRaster file
function openOra() {
    var path = fileDialog.currentFilePath
    currentPageItem.canvasArea.oraPath = path
    var layersList = openRaster.readAttributes(path)

    addPage(fileDialog.currentFileName)
    for (var i = layersList.length - 1; i > -1; i-- ) {
        addLayer(layersList[i].name)
        var src = layersList[i].src
        var layerId = pagesModel.get(currentPageIndex).layerModel.get(0).layerId
        openRaster.readPixmap(path, src, layerId)
    }
    console.log("open complete")
    fileDialog.visible = false
}

// Save OpenRaster file with new name
function saveAsOra() {
    var path = fileDialog.currentFilePath
    if (path.substr(-3) !== ".ora")
        path += ".ora"
    currentPageItem.canvasArea.oraPath = path
    saveOra()
    fileDialog.visible = false
}

// Save OpenRaster file
function saveOra() {
    var path = currentPageItem.canvasArea.oraPath
    var layerModel = pagesModel.get(currentPageIndex).layerModel
    var layerList = []
    for (var i = 0; i < layerModel.count; i++) {
        layerList.push({ "name": layerModel.get(i).name,
                         "layerId": layerModel.get(i).layerId,
                         "enable": layerModel.get(i).enable})
    }
    openRaster.write(path, imageSize, layerList)
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

// Converts HSV to HSL
function hslColor(hue, saturation, value, alpha) {
    var lightness = (2 - saturation) * value
    var newSaturation = saturation * value / (lightness <= 1 ? lightness : 2 - lightness)
    lightness = lightness / 2
    return Qt.hsla(hue, newSaturation, lightness, alpha)
}

// Get filename from path
function fileFromPath(path) {
    return path.substring(0, path.lastIndexOf("/") + 1)
}

// Get folder from path
function folderFromPath(path) {
    return path.replace(/^.*[\\\/]/, '')
}
