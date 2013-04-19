function start() {
    return {
        name: "Start",
        undo: function() {},
        redo: function() {}
    }
}

function paint() {
    var startPos = brushEngine.startPos()
    var undoArea = brushEngine.undoArea()
    var redoArea = brushEngine.redoArea()
    return {
        name: "Paint",
        undo: function() {
            imgProcessor.setPixmapArea(startPos, undoArea, currentLayerId)
            pathView.currentItem.update()
        },
        redo: function() {
            imgProcessor.setPixmapArea(startPos, redoArea, currentLayerId)
            pathView.currentItem.update()
        }
    }
}

function clear() {
    var startPos = Qt.point(0, 0)
    var undoArea = brushEngine.currentArea()
    return {
        name: "Clear",
        undo: function() {
            imgProcessor.setPixmapArea(startPos, undoArea, currentLayerId)
            pathView.currentItem.update()
        },
        redo: function() {
            brushEngine.clear()
            pathView.currentItem.update()
        }
    }
}

function fillColor() {
    var startPos = Qt.point(0, 0)
    var redoColor = colorPicker.color
    var undoArea = brushEngine.currentArea()
    imgProcessor.fillColor(currentLayerId, redoColor)
    pathView.currentItem.update()
    var redoArea = brushEngine.currentArea()
    return {
        name: "Fill Color",
        undo: function() {
            imgProcessor.setPixmapArea(startPos, undoArea, currentLayerId)
            pathView.currentItem.update()
        },
        redo: function() {
            imgProcessor.setPixmapArea(startPos, redoArea, currentLayerId)
            pathView.currentItem.update()
        }
    }
}

function changeLayer(prevLayerIndex, newLayerIndex) {
    var undoLayerIndex = prevLayerIndex
    var redoLayerIndex = newLayerIndex
    return {
        name: "Change Layer",
        undo: function() {
            currentLayerIndex = undoLayerIndex
        },
        redo: function() {
            currentLayerIndex = redoLayerIndex
        }
    }
}

function addLayer() {
    var redoLayerIndex = currentLayerIndex
    var layerName = layerModel.get(redoLayerIndex).name
    return {
        name: "Add Layer",
        undo: function() {
            Utils.deleteLayer(redoLayerIndex)
        },
        redo: function() {
            Utils.addLayer(layerName)
            currentLayerIndex = redoLayerIndex
        }
    }
}

function deleteLayer(layerIndex) {
    var redoLayerIndex = layerIndex
    var layerName = layerModel.get(layerIndex).name
    var currentIndexBackUp = currentLayerIndex
    currentLayerIndex = layerIndex
    var undoArea = brushEngine.currentArea()
    currentLayerIndex = currentIndexBackUp
    delete currentIndexBackUp

    return {
        name: "Delete Layer",
        undo: function() {
            var currentIndexBackUp = currentLayerIndex
            var startPos = Qt.point(0, 0)
            Utils.addLayer(layerName)
            if (currentLayerIndex < 0) currentLayerIndex = 0
            var layerId = layerModel.get(currentLayerIndex).layerId
            imgProcessor.setPixmapArea(startPos, undoArea, layerId)
            if (currentIndexBackUp >= 0) {
                layerModel.move(currentLayerIndex, redoLayerIndex, 1)
                currentLayerIndex = currentIndexBackUp
            }
        },
        redo: function() {
            Utils.deleteLayer(redoLayerIndex)
        }
    }
}

function raiseLayer() {
    return {
        name: "Raise Layer",
        undo: function() {
            layerModel.move(currentLayerIndex, currentLayerIndex + 1, 1)
        },
        redo: function() {
            layerModel.move(currentLayerIndex, currentLayerIndex - 1, 1)
        }
    }
}

function lowerLayer() {
    return {
        name: "Lower Layer",
        undo: function() {
            layerModel.move(currentLayerIndex, currentLayerIndex - 1, 1)
        },
        redo: function() {
            layerModel.move(currentLayerIndex, currentLayerIndex + 1, 1)
        }
    }
}

function mergeLayer() {
    var layerId1 = currentLayerId
    var layerId2 = layerModel.get(currentLayerIndex + 1).layerId
    var layerIdList = [layerId1, layerId2]
    var pixmapList = imgProcessor.mergePixmap(layerIdList)
    var mergeLayerIndex = currentLayerIndex
    var layerName = layerModel.get(mergeLayerIndex).name
    currentLayerIndex++
    currentPageItem.canvasArea.pathView.currentItem.update()
    currentLayerIndex--
    Utils.deleteLayer(currentLayerIndex)
    return {
        name: "Merge Layer",
        undo: function() {
            var startPos = Qt.point(0, 0)
            imgProcessor.setPixmapArea(startPos, pixmapList[1], currentLayerId)
            Utils.addLayer(layerName)
            if (currentLayerIndex < 0) currentLayerIndex = 0
            var layerId = layerModel.get(currentLayerIndex).layerId
            imgProcessor.setPixmapArea(startPos, pixmapList[0], currentLayerId)
            if (mergeLayerIndex >= 0) {
                layerModel.move(currentLayerIndex, mergeLayerIndex, 1)
                currentLayerIndex = mergeLayerIndex
            }
            currentLayerIndex++
            currentPageItem.canvasArea.pathView.currentItem.update()
            currentLayerIndex--
        },
        redo: function() {
            layerIdList = [currentLayerId, layerModel.get(currentLayerIndex + 1).layerId]
            imgProcessor.mergePixmap(layerIdList)
            currentLayerIndex++
            currentPageItem.canvasArea.pathView.currentItem.update()
            currentLayerIndex--
            Utils.deleteLayer(mergeLayerIndex)
        }
    }
}


function cloneLayer() {
    return {
        name: "Clone Layer",
        undo: function() {
            console.log("undo-clone-layer");
        },
        redo: function() {
            console.log("redo-clone-layer");
        }
    }
}

function renameLayer() {
    return {
        name: "Rename Layer",
        undo: function() {
            console.log("undo-rename-layer");
        },
        redo: function() {
            console.log("redo-rename-layer");
        }
    }
}
