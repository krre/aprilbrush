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

function clear(undoArea) {
    var _undoArea = undoArea
    return {
        name: qsTr("Clear"),
        undo: function() {
            canvas.getContext("2d").drawImage(_undoArea, 0, 0)
            canvas.requestPaint()
        },
        redo: function() {
            canvas.clear(true)
        }
    }
}

function changeLayer(undoIndex, redoIndex) {
    var _undoIndex = undoIndex
    var _redoIndex = redoIndex
    return {
        name: qsTr("Change Layer"),
        undo: function() {
            layerManager.layerView.currentRow = _undoIndex
        },
        redo: function() {
            layerManager.layerView.currentRow = _redoIndex
        }
    }
}

function addLayer(name, color) {
    var _name = name
    var _color = color
    var redoLayerIndex = layerManager.layerView.currentRow
    return {
        name: qsTr("Add Layer"),
        undo: function() {
            layerManager.deleteLayer(redoLayerIndex)
        },
        redo: function() {
            var insertIndex = layerView.currentRow < 0 ? 0 : layerView.currentRow
            layerModel.insert(insertIndex, { name: _name, color: _color, layerVisible: true, blocked: false })
            layerManager.layerView.currentRow = insertIndex
        }
    }
}

function deleteLayer(index) {
    var _index = index
    var _name = layerModel.get(index).name
    var _color = layerModel.get(index).color
    var _undoArea = currentTab.canvas.getContext("2d").getImageData(0, 0, imageSize.width, imageSize.height)
    return {
        name: qsTr("Delete Layer"),
        undo: function() {
            layerModel.insert(_index, { name: _name, color: _color, layerVisible: true, blocked: false })
            layerManager.layerView.currentRow = _index
            currentTab.canvas.onReady.connect(function() {
                currentTab.canvas.getContext("2d").drawImage(_undoArea, 0, 0)
                currentTab.canvas.requestPaint()
            })
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
            layerModel.move(layerManager.layerView.currentRow, layerManager.layerView.currentRow + 1, 1)
        },
        redo: function() {
            layerModel.move(layerManager.layerView.currentRow, layerManager.layerView.currentRow - 1, 1)
        }
    }
}

function lowerLayer() {
    return {
        name: qsTr("Lower Layer"),
        undo: function() {
            layerModel.move(layerManager.layerView.currentRow, layerManager.layerView.currentRow - 1, 1)
        },
        redo: function() {
            layerModel.move(layerManager.layerView.currentRow, layerManager.layerView.currentRow + 1, 1)
        }
    }
}

function mergeLayer() {
    var _undoAreaUp = currentTab.canvas.getContext("2d").getImageData(0, 0, imageSize.width, imageSize.height)
    var layerDown = layerModel.get(currentLayerIndex + 1)
    var _undoAreaDown = layerDown.canvas.getContext("2d").getImageData(0, 0, imageSize.width, imageSize.height)
    var _nameUp = layerModel.get(currentLayerIndex).name
    var _colorUp = layerModel.get(currentLayerIndex).color
    var _indexUp = currentLayerIndex
    return {
        name: qsTr("Merge Layer"),
        undo: function() {
            currentTab.canvas.getContext("2d").drawImage(_undoAreaDown, 0, 0)
            currentTab.canvas.requestPaint()
            layerModel.insert(currentLayerIndex, { name: _nameUp, color: _colorUp, layerVisible: true, blocked: false })
            layerManager.layerView.currentRow = _indexUp
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
