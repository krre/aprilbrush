/* AprilBrush - Digital Painting Software
 * Copyright (C) 2012-2014 Vladimir Zarypov <krre31@gmail.com>
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
        name: qsTr("Start"),
        undo: function() {},
        redo: function() {}
    }
}

function paint(startPos, undoArea, redoArea, alpha) {
    var _startPos = Qt.point(startPos.x, startPos.y)
    var _undoArea = undoArea
    var _redoArea = redoArea
    var _alpha = alpha

    return {
        name: qsTr("Paint"),
        undo: function() {
            canvas.getContext("2d").clearRect(_startPos.x, _startPos.y,  _undoArea.width, _undoArea.height)
            canvas.getContext("2d").drawImage(_undoArea, _startPos.x, _startPos.y)
            canvas.requestPaint()
        },
        redo: function() {
            var ctx = canvas.getContext("2d")
            ctx.save()
            ctx.globalAlpha = _alpha
            ctx.drawImage(_redoArea, _startPos.x, _startPos.y)
            ctx.restore()
            canvas.requestPaint()
        }
    }
}

function clear() {
    var startPos = Qt.point(0, 0)
//    var undoArea = brushEngine.currentArea()
    return {
        name: qsTr("Clear"),
        undo: function() {
            print("clear undo")
//            imgProcessor.setPixmapArea(startPos, undoArea, currentLayerId)
//            tabContent.canvasArea.pathView.currentItem.update()
        },
        redo: function() {
            print("clear redo")
            canvas.clear(true)
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
            layerManager.tableView.currentRow = undoLayerIndex
        },
        redo: function() {
            layerManager.tableView.currentRow = redoLayerIndex
        }
    }
}

function addLayer() {
    var redoLayerIndex = layerManager.tableView.currentRow
    var layerName = layerModel.get(redoLayerIndex).name
    return {
        name: "Add Layer",
        undo: function() {
            Utils.deleteLayer(redoLayerIndex)
        },
        redo: function() {
            Utils.addLayer(layerName)
            layerManager.tableView.currentRow = redoLayerIndex
        }
    }
}

function deleteLayer(layerIndex) {
    var redoLayerIndex = layerIndex
    var layerName = layerModel.get(layerIndex).name
    var currentIndexBackUp = tableView.currentRow
    tableView.currentRow = layerIndex
    var undoArea = brushEngine.currentArea()
    tableView.currentRow = currentIndexBackUp
    delete currentIndexBackUp

    return {
        name: "Delete Layer",
        undo: function() {
            var currentLayerIndex = tableView.currentRow
            var currentIndexBackUp = currentLayerIndex
            var startPos = Qt.point(0, 0)
            Utils.addLayer(layerName)
            if (currentLayerIndex < 0) currentLayerIndex = 0
            var layerId = layerModel.get(currentLayerIndex).layerId
            imgProcessor.setPixmapArea(startPos, undoArea, layerId)
            if (currentIndexBackUp >= 0) {
                layerModel.move(currentLayerIndex, redoLayerIndex, 1)
                tableView.currentRow = currentIndexBackUp
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
            layerModel.move(tableView.currentRow, tableView.currentRow + 1, 1)
        },
        redo: function() {
            layerModel.move(tableView.currentRow, tableView.currentRow - 1, 1)
        }
    }
}

function lowerLayer() {
    return {
        name: "Lower Layer",
        undo: function() {
            layerModel.move(tableView.currentRow, tableView.currentRow - 1, 1)
        },
        redo: function() {
            layerModel.move(tableView.currentRow, tableView.currentRow + 1, 1)
        }
    }
}

function mergeLayer() {
    var currentLayerIndex = tableView.currentRow
    var layerId1 = currentLayerId
    var layerId2 = layerModel.get(tableView.currentRow + 1).layerId
    var layerIdList = [layerId1, layerId2]
    var pixmapList = imgProcessor.mergePixmap(layerIdList)
    var mergeLayerIndex = currentLayerIndex
    var layerName = layerModel.get(mergeLayerIndex).name
    tableView.currentRow++
    tabContent.canvasArea.pathView.currentItem.update()
    tableView.currentRow--
    Utils.deleteLayer(tableView.currentRow)
    return {
        name: "Merge Layer",
        undo: function() {
            var startPos = Qt.point(0, 0)
            imgProcessor.setPixmapArea(startPos, pixmapList[1], currentLayerId)
            Utils.addLayer(layerName)
            if (tableView.currentRow < 0) tableView.currentRow = 0
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
