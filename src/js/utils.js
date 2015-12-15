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
    var list = []
    for (var i = 0; i < layerModel.count; i++) {
        list.push(layerModel.get(i).canvasItem)
    }
    colorPicker.color = coreLib.pickColor(pos, list)
}

function rgbToHex(r, g, b) {
    if (r > 255 || g > 255 || b > 255)
        throw "Invalid color component";
    return ((r << 16) | (g << 8) | b).toString(16);
}
