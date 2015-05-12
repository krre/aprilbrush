.import "undo.js" as Undo

// Open OpenRaster file
function openOra(filePath) {
    layerModel.clear()
    undoModel.clear()
    var layersList = coreLib.readOra(filePath)
    var selectedIndex = 0

    for (var i = 0; i < layersList.length; i++) {
        var layerMap = layersList[i]
        if (layerMap.selected === "true") {
            selectedIndex = i
        }
        layerModel.append({ name: layerMap.name,
                              isVisible: layerMap.visibility === "visible",
                              isLock: layerMap["edit-locked"] === "true",
                              isBackground: layerMap.aprilbrush_background === "true"
                          })
    }

    var loadCounter = 0

    canvasArea.canvasView.onCreated.connect(function load(index, canvas) {
        var image = layersList[index].image
        canvas.loadImage(image)
        canvas.onImageLoaded.connect(function draw() {
            var context = canvas.getContext("2d")
            context.drawImage(image, 0, 0)
            canvas.requestPaint()
            canvas.unloadImage(image)
            if (layerModel.get(index).isBackground) {
                var p = context.getImageData(0, 0, 1, 1).data
                var hex = "#" + ("000000" + rgbToHex(p[0], p[1], p[2])).slice(-6)
                canvasArea.bgColor = hex
            }
        })
        if (++loadCounter === layersList.length) {
            canvasArea.canvasView.onCreated.disconnect(load)
        }
    })

    layerManager.layerView.currentIndex = selectedIndex

    oraPath = filePath
    fileName = fileFromPath(oraPath)
    canvasArea.resetTransform()
    undoManager.add(Undo.start())
    isDirty = false
    console.log("open: " + path)
}

// Save OpenRaster file with new name
function saveAsOra(filePath) {
    var path = filePath.toString()
    if (path.substr(-4) !== ".ora") {
        path += ".ora"
    }
    oraPath = filePath
    fileName = fileFromPath(oraPath)
    saveOra()
}

// Save OpenRaster file
function saveOra() {
    var path = oraPath
    var layerList = []
    for (var i = 0; i < layerModel.count; i++) {
        var layerMap = {}
        var attributes = layerModel.get(i)
        for (var prop in attributes) {
            layerMap[prop] = attributes[prop]
        }
        layerMap.isSelected = (currentLayerIndex == i)
        var image = layerModel.get(i).canvas.toDataURL()
        image = image.substring(22, image.length) // cutting first block "data:image/png;base64,"
        layerMap.image = image
        layerList.push(layerMap)
    }
    coreLib.writeOra(path, imageSize, layerList)
    isDirty = false
    console.log("save: " + path)
}

// Export PNG file
function exportPng(filePath) {
    var path = coreLib.urlToPath(filePath)
    if (path.substr(-4) !== ".png") {
        path += ".png"
    }

    var finalCanvas = canvasArea.exportCanvas.createObject(canvasArea)
    finalCanvas.onFinished.connect(function() {
        finalCanvas.save(path)
        finalCanvas.destroy()
        console.log("export: " + path)
    })
}

// Pick color from canvas
function pickColor(pos) {
    var ctx = pickCanvas.getContext("2d")
    ctx.fillStyle = bgColor
    ctx.fillRect(0, 0, 1, 1)
    var isColor = false
    for (var i = layerModel.count - 1; i > -1; i--) {
        var layer = layerModel.get(i)
        if (layer.isVisible) {
            var canvas = layer.canvas
            var image = canvas.getContext("2d").getImageData(pos.x, pos.y, 1, 1)
            ctx.drawImage(image, 0, 0)
            isColor = true
        }
    }

    if (isColor) {
        var p = ctx.getImageData(0, 0, 1, 1).data
        var hex = "#" + ("000000" + rgbToHex(p[0], p[1], p[2])).slice(-6)
        colorPicker.color = hex
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

// Get filename from path
function fileFromPath(path) {
    return path.substr(path.lastIndexOf("/") + 1)
}

// Get folder from path
function folderFromPath(path) {
    return path.replace(/^.*[\\\/]/, '')
}

function createDynamicObject(parent, url, properties) {
    var component = Qt.createComponent(url)
    var errorMessage = component.errorString()
    if (errorMessage) {
        print("Error loading component " + url + ":", errorMessage)
    } else {
        return component.createObject(parent, properties ? properties : {})
    }
}
