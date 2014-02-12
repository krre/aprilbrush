/* AprilBrush - Digital Painting Software
 * Copyright (C) 2012-2013 Vladimir Zarypov <krre31@gmail.com>
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation;
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 */

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
            tabContent.canvasArea.pathView.currentItem.update()
        },
        redo: function() {
            brushEngine.clear()
            tabContent.canvasArea.pathView.currentItem.update()
        }
    }
}

function fillColor() {
    var startPos = Qt.point(0, 0)
    var redoColor = colorPicker.color
    var undoArea = brushEngine.currentArea()
    imgProcessor.fillColor(currentLayerId, redoColor)
    tabContent.canvasArea.pathView.currentItem.update()
    var redoArea = brushEngine.currentArea()
    return {
        name: "Fill Color",
        undo: function() {
            imgProcessor.setPixmapArea(startPos, undoArea, currentLayerId)
            tabContent.canvasArea.pathView.currentItem.update()
        },
        redo: function() {
            imgProcessor.setPixmapArea(startPos, redoArea, currentLayerId)
            tabContent.canvasArea.pathView.currentItem.update()
        }
    }
}

function changeLayer(prevLayerIndex, newLayerIndex) {
    var undoLayerIndex = prevLayerIndex
    var redoLayerIndex = newLayerIndex
    return {
        name: "Change Layer",
        undo: function() {
            layerManager.layerView.currentIndex = undoLayerIndex
        },
        redo: function() {
            layerManager.layerView.currentIndex = redoLayerIndex
        }
    }
}

function addLayer() {
    var redoLayerIndex = layerManager.layerView.currentIndex
    var layerName = layerModel.get(redoLayerIndex).name
    return {
        name: "Add Layer",
        undo: function() {
            Utils.deleteLayer(redoLayerIndex)
        },
        redo: function() {
            Utils.addLayer(layerName)
            layerManager.layerView.currentIndex = redoLayerIndex
        }
    }
}

function deleteLayer(layerIndex) {
    var redoLayerIndex = layerIndex
    var layerName = layerModel.get(layerIndex).name
    var currentIndexBackUp = layerView.currentIndex
    layerView.currentIndex = layerIndex
    var undoArea = brushEngine.currentArea()
    layerView.currentIndex = currentIndexBackUp
    delete currentIndexBackUp

    return {
        name: "Delete Layer",
        undo: function() {
            var currentLayerIndex = layerView.currentIndex
            var currentIndexBackUp = currentLayerIndex
            var startPos = Qt.point(0, 0)
            Utils.addLayer(layerName)
            if (currentLayerIndex < 0) currentLayerIndex = 0
            var layerId = layerModel.get(currentLayerIndex).layerId
            imgProcessor.setPixmapArea(startPos, undoArea, layerId)
            if (currentIndexBackUp >= 0) {
                layerModel.move(currentLayerIndex, redoLayerIndex, 1)
                layerView.currentIndex = currentIndexBackUp
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
            layerModel.move(layerView.currentIndex, layerView.currentIndex + 1, 1)
        },
        redo: function() {
            layerModel.move(layerView.currentIndex, layerView.currentIndex - 1, 1)
        }
    }
}

function lowerLayer() {
    return {
        name: "Lower Layer",
        undo: function() {
            layerModel.move(layerView.currentIndex, layerView.currentIndex - 1, 1)
        },
        redo: function() {
            layerModel.move(layerView.currentIndex, layerView.currentIndex + 1, 1)
        }
    }
}

function mergeLayer() {
    var currentLayerIndex = layerView.currentIndex
    var layerId1 = currentLayerId
    var layerId2 = layerModel.get(layerView.currentIndex + 1).layerId
    var layerIdList = [layerId1, layerId2]
    var pixmapList = imgProcessor.mergePixmap(layerIdList)
    var mergeLayerIndex = currentLayerIndex
    var layerName = layerModel.get(mergeLayerIndex).name
    layerView.currentIndex++
    tabContent.canvasArea.pathView.currentItem.update()
    layerView.currentIndex--
    Utils.deleteLayer(layerView.currentIndex)
    return {
        name: "Merge Layer",
        undo: function() {
            var startPos = Qt.point(0, 0)
            imgProcessor.setPixmapArea(startPos, pixmapList[1], currentLayerId)
            Utils.addLayer(layerName)
            if (layerView.currentIndex < 0) layerView.currentIndex = 0
            var layerId = layerModel.get(currentLayerIndex).layerId
            imgProcessor.setPixmapArea(startPos, pixmapList[0], currentLayerId)
            if (mergeLayerIndex >= 0) {
                layerModel.move(currentLayerIndex, mergeLayerIndex, 1)
                currentLayerIndex = mergeLayerIndex
            }
            currentLayerIndex++
            tabContent.canvasArea.pathView.currentItem.update()
            currentLayerIndex--
        },
        redo: function() {
            layerIdList = [currentLayerId, layerModel.get(currentLayerIndex + 1).layerId]
            imgProcessor.mergePixmap(layerIdList)
            currentLayerIndex++
            tabContent.canvasArea.pathView.currentItem.update()
            currentLayerIndex--
            Utils.deleteLayer(mergeLayerIndex)
        }
    }
}

function cloneLayer() {
    var layerName = layerModel.get(currentLayerIndex).name
    var cloneArea = brushEngine.currentArea()
    Utils.addLayer(layerName)
    imgProcessor.setPixmapArea(Qt.point(0, 0), cloneArea, currentLayerId)
    return {
        name: "Clone Layer",
        undo: function() {
            Utils.deleteLayer(currentLayerIndex)
        },
        redo: function() {
            var cloneArea = brushEngine.currentArea()
            Utils.addLayer(layerName)
            imgProcessor.setPixmapArea(Qt.point(0, 0), cloneArea, currentLayerId)
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
