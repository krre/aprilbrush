// Adds prefix zero to number
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
    currentPage.canvasArea.oraPath = path
    // Read layer attributes
    openRaster.readAttributes(path)
    var layersList = openRaster.layersNameList()
    console.log(layersList)

    pagesModel.append({name: fileDialog.currentFileName,
                          layerSet: [],
                          undoSet: []
                      })

    //pageManager.pagesView.currentIndex = pagesModel.count - 1
    var canvas = currentPage.canvasArea.pathView
    canvas.currentIndexBind = false

    for (var i = 0; i < layersList.length; i++)
    {
        //pagesModel.get(pageManager.pagesView.currentIndex).layerSet.append({ name: layersList[i], colorImage: "transparent", enable: true })
        pagesModel.get(pagesModel.count - 1).layerSet.append({ name: layersList[i], colorImage: "transparent", enable: true })
        canvas.currentIndex = i
        openRaster.setPixmap(canvas.currentItem, i)
        //console.log(canvas.currentItem)
    }


/*
    for (i = 0; i < canvas.count; i++) {
        canvas.currentIndex = i
        console.log(canvas.currentItem)
        openRaster.setPixmap(canvas.currentItem, i)
    }*/
    canvas.currentIndexBind = true
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
