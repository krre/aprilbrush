.import "undo.js" as Undo

function createDynamicObject(parent, url, properties) {
    var component = Qt.createComponent(url)
    var errorMessage = component.errorString()
    if (errorMessage) {
        print(errorMessage)
    } else {
        return component.createObject(parent, properties || {})
    }
}

function movePanelToDocker(panel, dock) {
    var tab = dock.addTab(panel.title)
    tab.active = true
    tab.setSource("qrc:/qml/components/Dummy.qml")
    var index = dock.count - 1
    panel.parent = dock.getTab(index).item
    panel.anchors.fill = dock.getTab(index).item
    panel.visible = true
}

function addRecentFile(path) {
    var model = mainMenu.recentFilesModel
    // Prevention of duplication of filePath and raising it on top.
    for (var i = 0; i < model.count; i++) {
        if (model.get(i).filePath === path) {
            model.remove(i)
        }
    }
    model.insert(0, { filePath: path })
    var maxRecentFiles = 10
    if (model.count === maxRecentFiles + 1) {
        model.remove(maxRecentFiles)
    }
}

function newTab(title, withoutLayer) {
    title = title || qsTr("Unnamed")
    var tab = tabView.addTab(title)
    tab.setSource("qrc:/qml/main/WorkArea.qml", { title: title })
    tabView.currentIndex = tabView.count - 1
    if (!withoutLayer) {
        layerManager.addLayer()
        undoManager.clear()
    }
}

function openOra(filePath) {
    newTab(coreLib.pathToFileName(filePath), true)

    var layersList = coreLib.readOra(filePath)
    var selectedIndex = 0

    for (var i = 0; i < layersList.length; i++) {
        var layer = layersList[i]
        if (layer.selected === "true") {
            selectedIndex = i
        }
        layerModel.append({ name: layer.name,
                              isVisible: layer.visibility === "visible",
                              isLock: layer["edit-locked"] === "true",
//                              isBackground: layer.aprilbrush_background === "true"
                              image: layer.image
                          })
    }

    layerManager.currentIndex = selectedIndex
    currentTab.oraPath = filePath
    addRecentFile(filePath)
    undoManager.add(Undo.start())
}

function saveAsOra(filePath) {
    if (filePath.substr(-4) !== ".ora") {
        filePath += ".ora"
    }
    currentTab.oraPath = filePath
    saveOra()
}

function saveOra() {
    var layerList = []
    for (var i = 0; i < layerModel.count; i++) {
        var map = {}
        var attributes = layerModel.get(i)
        for (var prop in attributes) {
            map[prop] = attributes[prop]
        }
        map.isSelected = (layerManager.currentIndex == i)
        map.canvasItem = layerModel.get(i).canvasItem
        layerList.push(map)
    }
    coreLib.writeOra(currentTab.oraPath, imageSize, layerList)
    currentTab.isDirty = false
}

function exportPng(filePath) {
    if (filePath.substr(-4) !== ".png") {
        filePath += ".png"
    }

    var list = []
    for (var i = 0; i < layerModel.count; i++) {
        list.push(layerModel.get(i).canvasItem)
    }

    coreLib.writePng(filePath, list)
}

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

function zeroFill(number, width)
{
    width -= number.toString().length;
    if (width > 0)
    {
        return new Array(width + (/\./.test(number) ? 2 : 1)).join('0') + number;
    }
    return number + ""; // always return a string
}

function hsvToHsl(h, s, v) {
    var l = (2 - s) * v / 2
    var computedS = s * v / (1 - Math.abs(2 * l - 1))
    return Qt.hsla(h, computedS, l, 1)
}

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

function rgbToHex(r, g, b) {
    if (r > 255 || g > 255 || b > 255)
        throw "Invalid color component";
    return ((r << 16) | (g << 8) | b).toString(16);
}

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

function fileFromPath(path) {
    return path.substr(path.lastIndexOf("/") + 1)
}

function folderFromPath(path) {
    return path.replace(/^.*[\\\/]/, '')
}

