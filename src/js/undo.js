function start() {
    return {
        name: qsTr("Start"),
        undo: function() {},
        redo: function() {}
    }
}

function paint() {
//    var startPos = brushEngine.startPos()
//    var undoArea = brushEngine.undoArea()
//    var redoArea = brushEngine.redoArea()
    return {
        name: "Paint",
        undo: function() {
        },
        redo: function() {
        }
    }
}


function clearLayer() {
    var undoArea = currentTab.canvasItem.byteArray()
    return {
        name: qsTr("Clear"),
        undo: function() {
            currentTab.canvasItem.setByteArray(undoArea)
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
    var _index = layerManager.currentIndex
    var _name = layerModel.get(_index).name
//    var _undoArea = canvasArea.canvas.getContext("2d").getImageData(0, 0, imageSize.width, imageSize.height)
    return {
        name: qsTr("Delete Layer"),
        undo: function() {
            var layerObj = layerManager.defaultLayer()
            layerObj.name = _name
            layerModel.insert(_index, layerObj)
            layerManager.currentIndex = _index
//            canvasArea.canvas.onReady.connect(function() {
//                canvasArea.canvas.getContext("2d").drawImage(_undoArea, 0, 0)
//                canvasArea.canvas.requestPaint()
//            })
        },
        redo: function() {
            layerModel.remove(_index)
        }
    }
}

function raiseLayer() {
    return {
        name: qsTr("Raise Layer"),
        undo: function() {
            layerModel.move(layerManager.currentIndex, layerManager.currentIndex + 1, 1)
        },
        redo: function() {
            layerModel.move(layerManager.currentIndex, layerManager.currentIndex - 1, 1)
        }
    }
}

function lowerLayer() {
    return {
        name: qsTr("Lower Layer"),
        undo: function() {
            layerModel.move(layerManager.currentIndex, layerManager.currentIndex - 1, 1)
        },
        redo: function() {
            layerModel.move(layerManager.currentIndex, layerManager.currentIndex + 1, 1)
        }
    }
}

function mergeLayer() {
    var _undoAreaUp = canvasArea.canvas.getContext("2d").getImageData(0, 0, imageSize.width, imageSize.height)
    var layerDown = layerModel.get(currentLayerIndex + 1)
    var _undoAreaDown = layerDown.canvas.getContext("2d").getImageData(0, 0, imageSize.width, imageSize.height)
    var _nameUp = layerModel.get(currentLayerIndex).name
    var _indexUp = layerManager.currentIndex
    return {
        name: qsTr("Merge Layer"),
        undo: function() {
            canvasArea.canvas.getContext("2d").drawImage(_undoAreaDown, 0, 0)
            canvasArea.canvas.requestPaint()
            var layerObj = layerManager.defaultLayer()
            layerObj.name = _nameUp
            layerModel.insert(currentLayerIndex, layerObj)
            layerManager.layerView.currentIndex = _indexUp
            layerModel.get(_indexUp).canvas.onReady.connect(function() {
                layerModel.get(_indexUp).canvas.getContext("2d").drawImage(_undoAreaUp, 0, 0)
                layerModel.get(_indexUp).canvas.requestPaint()
            })
        },
        redo: function() {
            layerDown.canvas.getContext("2d").drawImage(_undoAreaUp, 0, 0)
            layerDown.canvas.requestPaint()
            layerModel.remove(currentLayerIndex)
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
            var _name = layerModel.get(layerManager.currentIndex).name
//            var _duplicateArea = canvasArea.canvas.getContext("2d").getImageData(0, 0, imageSize.width, imageSize.height)
            var layerObj = layerManager.defaultLayer()
            layerObj.name = _name
            layerModel.insert(layerManager.currentIndex, layerObj)
//            layerManager.currentIndex = currentLayerIndex
//            layerModel.get(currentLayerIndex).canvas.onReady.connect(function() {
//                layerModel.get(currentLayerIndex).canvas.getContext("2d").drawImage(_duplicateArea, 0, 0)
//                layerModel.get(currentLayerIndex).canvas.requestPaint()
//            })
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
