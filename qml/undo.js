function start() {
    return {
        name: "Start",
        undo: function() {
            //console.log("undo-start");
        },
        redo: function() {
            //console.log("redo-start");
        }
    }
}

function paint() {
    var startPos = brush.startPos()
    var undoArea = brush.undoArea()
    var redoArea = brush.redoArea()
    return {
        name: "Paint",
        undo: function() {
            imgProcessor.setPixmapArea(startPos, undoArea, currentLayerId)
            pathView.currentItem.update()
            //console.log("undo-paint");
        },
        redo: function() {
            imgProcessor.setPixmapArea(startPos, redoArea, currentLayerId)
            pathView.currentItem.update()
            //console.log("redo-paint");
        }
    }
}

function clear() {
    var startPos = Qt.point(0, 0)
    var undoArea = brush.currentArea()
    return {
        name: "Clear",
        undo: function() {
            imgProcessor.setPixmapArea(startPos, undoArea, currentLayerId)
            pathView.currentItem.update()
            //console.log("undo-clear");
        },
        redo: function() {
            brush.clear()
            //console.log("redo-clear");
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
            //console.log("undo-change-layer");
        },
        redo: function() {
            currentLayerIndex = redoLayerIndex
            //console.log("redo-change-layer");
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
            //console.log("undo-add-layer");
        },
        redo: function() {
            Utils.addLayer(layerName)
            currentLayerIndex = redoLayerIndex
            //console.log("redo-add-layer");
        }
    }
}

function deleteLayer(layerIndex) {
    var redoLayerIndex = layerIndex
    var layerName = layerModel.get(layerIndex).name
    var currentIndexBackUp = currentLayerIndex
    currentLayerIndex = layerIndex
    var undoArea = brush.currentArea()
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
            //console.log("redo-delete-layer");
        }
    }
}

function raiseLayer() {
    return {
        name: "Raise Layer",
        undo: function() {
            layerModel.move(currentLayerIndex, currentLayerIndex + 1, 1)
            //console.log("undo-raise-layer");
        },
        redo: function() {
            layerModel.move(currentLayerIndex, currentLayerIndex - 1, 1)
            //console.log("redo-raise-layer");
        }
    }
}

function lowerLayer() {
    return {
        name: "Lower Layer",
        undo: function() {
            layerModel.move(currentLayerIndex, currentLayerIndex - 1, 1)
            //console.log("undo-lower-layer");
        },
        redo: function() {
            layerModel.move(currentLayerIndex, currentLayerIndex + 1, 1)
            //console.log("redo-lower-layer");
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
