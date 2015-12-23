function start() {
    return {
        name: qsTr("Start"),
        undo: function() {},
        redo: function() {}
    }
}

function paint() {
    var startPos = BrushEngine.startPos()
    var undoArea = BrushEngine.undoImage()
    var redoArea = BrushEngine.redoImage()
    var isHistory = false
    return {
        name: "Paint",
        undo: function() {
            canvasItem.setImage(undoArea, startPos)
        },
        redo: function() {
            if (!isHistory) {
                isHistory = true
            } else {
                canvasItem.setImage(redoArea, startPos)
            }
        }
    }
}


function clearLayer() {
    var undoArea = currentTab.canvasItem.image()
    return {
        name: qsTr("Clear"),
        undo: function() {
            currentTab.canvasItem.setImage(undoArea)
        },
        redo: function() {
            currentTab.canvasItem.clear()
        }
    }
}

function changeLayer(undoIndex, redoIndex) {
    return {
        name: qsTr("Change Layer"),
        undo: function() {
            layerManager.currentIndex = undoIndex
        },
        redo: function() {
            layerManager.currentIndex = redoIndex
        }
    }
}

function addLayer(name) {
    return {
        name: qsTr("Add Layer"),
        undo: function() {
            layerModel.remove(layerManager.currentIndex)
        },
        redo: function() {
            var insertIndex = layerManager.currentIndex < 0 ? 0 : layerManager.currentIndex
            var layer = layerManager.defaultLayer()
            layer.name = name
            layerModel.insert(insertIndex, layer)
            layerManager.currentIndex = insertIndex
        }
    }
}

function deleteLayer() {
    var index = layerManager.currentIndex
    var layer = layerManager.defaultLayer()
    layer.name = layerModel.get(index).name
    layer.isVisible = layerModel.get(index).isVisible
    layer.isLock = layerModel.get(index).isLock
    layer.image = coreLib.byteArrayToBase64(currentTab.canvasItem.image())
    return {
        name: qsTr("Delete Layer"),
        undo: function() {
            layerModel.insert(index, layer)
            layerManager.currentIndex = index
        },
        redo: function() {
            layerModel.remove(index)
        }
    }
}

function raiseLayer() {
    return {
        name: qsTr("Raise Layer"),
        undo: function() {
            layerModel.move(layerManager.currentIndex, layerManager.currentIndex + 1, 1)
            layerManager.currentIndex = layerManager.currentIndex + 1
        },
        redo: function() {
            layerModel.move(layerManager.currentIndex, layerManager.currentIndex - 1, 1)
            layerManager.currentIndex = layerManager.currentIndex - 1
        }
    }
}

function lowerLayer() {
    return {
        name: qsTr("Lower Layer"),
        undo: function() {
            layerModel.move(layerManager.currentIndex, layerManager.currentIndex - 1, 1)
            layerManager.currentIndex = layerManager.currentIndex - 1
        },
        redo: function() {
            layerModel.move(layerManager.currentIndex, layerManager.currentIndex + 1, 1)
            layerManager.currentIndex = layerManager.currentIndex + 1
        }
    }
}

function mergeLayer() {
    var indexUp = layerManager.currentIndex
    var layerUp = layerModel.get(indexUp)
    var undoAreaUp = layerUp.canvasItem.image()
    var nameUp = layerUp.name
    var isVisibleUp = layerUp.isVisible
    var isLockUp = layerUp.isLock

    var layerDown = layerModel.get(indexUp + 1)
    var undoAreaDown = layerDown.canvasItem.image()

    return {
        name: qsTr("Merge Layer"),
        undo: function() {
            currentTab.canvasItem.setImage(undoAreaDown)

            var layer = layerManager.defaultLayer()
            layer.name = nameUp
            layer.isVisible = isVisibleUp
            layer.isLock = isLockUp
            layer.image = coreLib.byteArrayToBase64(undoAreaUp)
            layerModel.insert(layerManager.currentIndex, layer)
            layerManager.layerView.currentIndex = indexUp
        },
        redo: function() {
            layerDown.canvasItem.drawImage(undoAreaUp)
            layerModel.remove(indexUp)
        }
    }
}

function duplicateLayer() {
    return {
        name: qsTr("Duplicate Layer"),
        undo: function() {
            layerModel.remove(layerManager.currentIndex)
        },
        redo: function() {
            var layer = layerManager.defaultLayer()
            layer.name = layerModel.get(layerManager.currentIndex).name
            layer.isVisble = layerModel.get(layerManager.currentIndex).isVisible
            layer.isLock = layerModel.get(layerManager.currentIndex).isLock
            layer.image = coreLib.byteArrayToBase64(currentTab.canvasItem.image())
            var index = layerManager.currentIndex
            layerModel.insert(layerManager.currentIndex, layer)
            layerManager.currentIndex = index
        }
    }
}

function renameLayer(undoName, redoName) {
    return {
        name: qsTr("Rename Layer"),
        undo: function() {
            layerModel.setProperty(layerManager.currentIndex, "name", undoName)
        },
        redo: function() {
            layerModel.setProperty(layerManager.currentIndex, "name", redoName)
        }
    }
}

function changeIsVisibileLayer(index) {
    var isVisible = layerModel.get(index).isVisible
    return {
        name: isVisible ? qsTr("Layer Unvisible") : qsTr("Layer Visible"),
        undo: function() {
            layerModel.setProperty(index, "isVisible", isVisible)
        },
        redo: function() {
            layerModel.setProperty(index, "isVisible", !isVisible)
        }
    }
}

function changeIsLockLayer(index) {
    var isLock = layerModel.get(index).isLock
    return {
        name: isLock ? qsTr("Layer Unlock") : qsTr("Layer Lock"),
        undo: function() {
            layerModel.setProperty(index, "isLock", isLock)
        },
        redo: function() {
            layerModel.setProperty(index, "isLock", !isLock)
        }
    }
}
