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

// Save OpenRaster file
function saveOra() {
    console.log(currentPage.canvasArea.oraPath)
}

// Save OpenRaster file with new name
function saveAsOra() {
    var path = fileDialog.currentFilePath
    currentPage.canvasArea.oraPath = path
    saveOra()
    fileDialog.visible = false
}

// Open OpenRaster file
function openOra() {
    var path = fileDialog.currentFilePath
    currentPage.canvasArea.oraPath = path
    fileDialog.visible = false
}

