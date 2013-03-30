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

    pagesModel.append({name: newPageName, layerSet: [], undoSet: [] })
    //console.log("pagesView " + pageManager.pagesView)
    pageManager.pagesView.currentIndex = pagesModel.count - 1

    if (!pageName) {
        addLayer(null, "white")
        addLayer()
    }
}

// Add new layer
function addLayer(layerName, color) {
    var newLayerName
    var layerSet = pagesModel.get(currentPageIndex).layerSet
    if (layerName)
        newLayerName = layerName
    else {
        if (layerSet.count) {
            // Calculate next number layer
            var maxNumLayer = 0;
            for (var layer = 0; layer < layerSet.count; layer++) {
                var numLayer = parseInt(layerSet.get(layer).name.substring(6), 10)
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
    layerSet.append({ name: newLayerName, colorImage: newColor, enable: true, layerId: newLayerId })
    // Set new layer as current
    if (layerSet.count > 1) {
        var selectedLayer = currentPageItem.layerManager.currentLayerIndex
        layerSet.move(layerSet.count - 1, selectedLayer, 1)
        currentPageItem.layerManager.currentLayerIndex = selectedLayer
    }
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

// Open OpenRaster file
function openOra() {
    var path = fileDialog.currentFilePath
    currentPageItem.canvasArea.oraPath = path
    // Read layer attributes
    openRaster.readAttributes(path)
    var layersList = openRaster.layersNameList()
    console.log(layersList)

    addPage(fileDialog.currentFileName)
    for (var i = layersList.length - 1; i > -1; i-- ) {
        addLayer(layersList[i])
        var layerId = pagesModel.get(currentPageIndex).layerSet.get(0).layerId
        console.log("layerId " + layerId + " i " + i)
        brush.setLayerId(layerId)
        console.log("source " + brush.source())
        openRaster.setPixmap(brush.source(), i)
    }


    console.log("open complete")

    fileDialog.visible = false
}

// Save OpenRaster file with new name
function saveAsOra() {
    var path = fileDialog.currentFilePath
    if (path.substr(-3) !== ".ora")
        path += ".ora"
    currentPage.canvasArea.oraPath = path
    saveOra()
    fileDialog.visible = false
}

// Save OpenRaster file
function saveOra() {
    //console.log(currentPage.canvasArea.oraPath)
    var canvas = currentPage.canvasArea.pathView
    canvas.currentIndexBind = false
    var currentLayer = canvas.currentIndex
    var paintedItemList = []
    var layersNameList = []

    for (var i = 0; i < canvas.count; i++) {
        // paintedItem objects
        canvas.currentIndex = i
        paintedItemList.push(canvas.currentItem)
        // layers name
        layersNameList.push(pagesModel.get(currentPage).layerSet.get(i).name)
    }
    canvas.currentIndexBind = true

    openRaster.write(currentPage.canvasArea.oraPath, imageSize, paintedItemList, layersNameList)

    currentPage.canvasArea.focusBind = false
    currentPage.canvasArea.focus = true
    currentPage.canvasArea.focusBind = true
}
