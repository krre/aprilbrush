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
            canvasArea.pathView.currentItem.setPixmapArea(startPos, undoArea)
            //console.log("undo-paint");
        },
        redo: function() {
            canvasArea.pathView.currentItem.setPixmapArea(startPos, redoArea)
            //console.log("redo-paint");
        }
    }
}

function clear() {
    var startPos = Qt.point(0, 0)
    //var undoArea = brush.currentArea()
    return {
        name: "Clear",
        undo: function() {
            canvasArea.pathView.currentItem.setPixmapArea(startPos, undoArea)
            //console.log("undo-clear");
        },
        redo: function() {
            brush.clear()
            //console.log("redo-clear");
        }
    }
}

function changeLayer(prevLayer, newLayer) {
    var undoLayer = prevLayer
    var redoLayer = newLayer
    return {
        name: "Change Layer",
        undo: function() {
            currentLayer = undoLayer
            //console.log("undo-change-layer");
        },
        redo: function() {
            currentLayer = redoLayer
            //console.log("redo-change-layer");
        }
    }
}

function addLayer(numLayer) {
    var redoLayer = numLayer
    var layerName = layerModel.get(numLayer).name
    return {
        name: "Add Layer",
        undo: function() {
            layerModel.remove(redoLayer)
            //console.log("undo-add-layer");
        },
        redo: function() {
            layerModel.insert(redoLayer, { name: layerName, colorImage: "transparent", enable: true })
            currentLayer = redoLayer
            //console.log("redo-add-layer");
        }
    }
}

function deleteLayer(numLayer) {
    var redoLayer = numLayer
    //var isCurrent = (currentLayer === numLayer)
    var layerName = layerModel.get(numLayer).name
    //var undoArea
    //console.log("currentLayer: " + currentLayer + " redoLayer: " + redoLayer + " isCurrent: " + isCurrent)
    /*
    if (!isCurrent) {
        var currentLayerIndex = currentLayer
        currentLayer = redoLayer
        brush.setSource(canvasArea.pathView.currentItem)
        undoArea = brush.currentArea()
        currentLayer = currentLayerIndex
    }
    else*/
        var undoArea = brush.currentArea()
    return {
        name: "Delete Layer",
        undo: function() {
            var currentLayerIndex = currentLayer
            layerModel.insert(redoLayer, { name: layerName, colorImage: "transparent", enable: true })
            currentLayer = redoLayer
            canvasArea.pathView.currentItem.setPixmapArea(Qt.point(0, 0), undoArea)
/*
            if (!isCurrent)
                currentLayer = currentLayerIndex*/

        },
        redo: function() {
            layerModel.remove(redoLayer)
            //console.log("redo-delete-layer");
        }
    }
}

function raiseLayer() {
    return {
        name: "Raise Layer",
        undo: function() {
            layerModel.move(currentLayer, currentLayer + 1, 1)
            //console.log("undo-raise-layer");
        },
        redo: function() {
            layerModel.move(currentLayer, currentLayer - 1, 1)
            //console.log("redo-raise-layer");
        }
    }
}

function lowerLayer() {
    return {
        name: "Lower Layer",
        undo: function() {
            layerModel.move(currentLayer, currentLayer - 1, 1)
            //console.log("undo-lower-layer");
        },
        redo: function() {
            layerModel.move(currentLayer, currentLayer + 1, 1)
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
