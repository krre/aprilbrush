.import QtQuick 2.6 as QtQuick
.import "undo.js" as Undo

function createDynamicObject(parent, url, properties) {
    var component = Qt.createComponent(url)
    if (component.status === QtQuick.Component.Ready) {
        return component.createObject(parent, properties || {})
    } else {
        print(component.errorString())
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

function saveRecentFiles() {
    var model = mainMenu.recentFilesModel
    var list = []
    for (var i = 0; i < model.count; i++) {
        var path = model.get(i).filePath
        if (path) {
            list.push(path)
        }
    }
    Settings.setList("RecentFiles", list)
}

function loadRecentFiles() {
    var list = Settings.list("RecentFiles")
    var model = mainMenu.recentFilesModel
    for (var i = 0; i < list.length; i++) {
        var path = list[i]
        if (Core.isFileExists(path)) {
            model.append({ filePath: path })
        }
    }
}

function newTab(title, withoutLayer, size) {
    title = title || qsTr("Unnamed")
    size = size || Qt.size(Settings.value("NewImage", "width", screenSize.width),
                           Settings.value("NewImage", "height", screenSize.heigth))
    var tab = tabView.addTab(title)
    tab.setSource("qrc:/qml/main/WorkArea.qml", { title: title, canvasSize: size })
    tabView.currentIndex = tabView.count - 1
    if (!withoutLayer) {
        layerManager.addLayer()
        undoManager.clear()
    }
}

function openOra(filePath) {
    var oraAttr = Core.readOraAttr(filePath)
    newTab(Core.pathToFileName(filePath), true, Qt.size(oraAttr.w, oraAttr.h))

    var layersList = Core.readOra(filePath)
    var selectedIndex = 0

    for (var i = 0; i < layersList.length; i++) {
        var layer = layersList[i]
        if (layer.selected === "true") {
            selectedIndex = i
        }
        layerModel.append({ name: layer.name,
                              isVisible: layer.visibility === "visible",
                              isLock: layer["edit-locked"] === "true",
                              image: layer.image
                          })
    }

    layerManager.currentIndex = selectedIndex
    currentTab.oraPath = filePath
    addRecentFile(filePath)
    undoManager.clear()
}

function saveAsOra(filePath) {
    if (filePath.substr(-4) !== ".ora") {
        filePath += ".ora"
    }
    currentTab.oraPath = filePath
    tabView.getTab(tabView.currentIndex).title = Core.pathToFileName(filePath)
    saveOra()
    addRecentFile(filePath)
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
    Core.writeOra(currentTab.oraPath, currentTab.canvasSize, layerList)
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

    Core.writePng(filePath, list)
}

function pickColor(pos) {
    var list = []
    for (var i = 0; i < layerModel.count; i++) {
        list.push(layerModel.get(i).canvasItem)
    }
    colorPicker.color = Core.pickColor(pos, list)
}

