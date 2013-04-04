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
        }
    }
}

function fillColor() {
    var startPos = Qt.point(0, 0)
    var redoColor = colorPicker.pickColor
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

function addLayer(layerIndex) {
    var redoLayerIndex = layerIndex
    var layerName = layerModel.get(layerIndex).name
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
