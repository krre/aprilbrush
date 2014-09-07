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
            currentTab.canvas.getContext("2d").clearRect(_startPos.x, _startPos.y,  _undoArea.width, _undoArea.height)
            currentTab.canvas.getContext("2d").drawImage(_undoArea, _startPos.x, _startPos.y)
            currentTab.canvas.requestPaint()
        },
        redo: function() {
            var ctx = canvas.getContext("2d")
            ctx.save()
            ctx.globalAlpha = _alpha
            ctx.drawImage(_redoArea, _startPos.x, _startPos.y)
            ctx.restore()
            currentTab.canvas.requestPaint()
        }
    }
}

function clearLayer() {
    var _undoArea = currentTab.canvas.getContext("2d").getImageData(0, 0, imageSize.width, imageSize.height)
    return {
        name: qsTr("Clear"),
        undo: function() {
            currentTab.canvas.getContext("2d").drawImage(_undoArea, 0, 0)
            currentTab.canvas.requestPaint()
        },
        redo: function() {
            currentTab.canvas.clear()
        }
    }
}

function changeLayer(undoIndex, redoIndex) {
    var _undoIndex = undoIndex
    var _redoIndex = redoIndex
    return {
        name: qsTr("Change Layer"),
        undo: function() {
            layerManager.layerView.currentIndex = _undoIndex
        },
        redo: function() {
            layerManager.layerView.currentIndex = _redoIndex
        }
    }
}

function addLayer(name) {
    var _name = name
    var redoLayerIndex = layerManager.layerView.currentIndex
    return {
        name: qsTr("Add Layer"),
        undo: function() {
            layerManager.deleteLayer(redoLayerIndex)
        },
        redo: function() {
            var insertIndex = layerView.currentIndex < 0 ? 0 : layerView.currentIndex
            var layerObj = layerManager.defaultLayer()
            layerObj.name = name
            layerModel.insert(insertIndex, layerObj)
            layerManager.layerView.currentIndex = insertIndex
        }
    }
}

function deleteLayer(index) {
    var _index = index
    var _name = layerModel.get(index).name
    var _undoArea = currentTab.canvas.getContext("2d").getImageData(0, 0, imageSize.width, imageSize.height)
    return {
        name: qsTr("Delete Layer"),
        undo: function() {
            layerModel.insert(_index, { name: _name, isVisible: true, isBlocked: false })
            layerManager.layerView.currentIndex = _index
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
            layerModel.move(layerManager.layerView.currentIndex, layerManager.layerView.currentIndex + 1, 1)
        },
        redo: function() {
            layerModel.move(layerManager.layerView.currentIndex, layerManager.layerView.currentIndex - 1, 1)
        }
    }
}

function lowerLayer() {
    return {
        name: qsTr("Lower Layer"),
        undo: function() {
            layerModel.move(layerManager.layerView.currentIndex, layerManager.layerView.currentIndex - 1, 1)
        },
        redo: function() {
            layerModel.move(layerManager.layerView.currentIndex, layerManager.layerView.currentIndex + 1, 1)
        }
    }
}

function mergeLayer() {
    var _undoAreaUp = currentTab.canvas.getContext("2d").getImageData(0, 0, imageSize.width, imageSize.height)
    var layerDown = layerModel.get(currentLayerIndex + 1)
    var _undoAreaDown = layerDown.canvas.getContext("2d").getImageData(0, 0, imageSize.width, imageSize.height)
    var _nameUp = layerModel.get(currentLayerIndex).name
    var _indexUp = currentLayerIndex
    return {
        name: qsTr("Merge Layer"),
        undo: function() {
            currentTab.canvas.getContext("2d").drawImage(_undoAreaDown, 0, 0)
            currentTab.canvas.requestPaint()
            layerModel.insert(currentLayerIndex, { name: _nameUp, isVisible: true, isBlocked: false })
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
            layerModel.remove(currentLayerIndex)
        },
        redo: function() {
            var _name = layerModel.get(currentLayerIndex).name
            var _duplicateArea = currentTab.canvas.getContext("2d").getImageData(0, 0, imageSize.width, imageSize.height)
            layerModel.insert(currentLayerIndex, { name: _name, isVisible: true, isBlocked: false })
            layerManager.layerView.currentIndex = currentLayerIndex
            layerModel.get(currentLayerIndex).canvas.onReady.connect(function() {
                layerModel.get(currentLayerIndex).canvas.getContext("2d").drawImage(_duplicateArea, 0, 0)
                layerModel.get(currentLayerIndex).canvas.requestPaint()
            })
        }
    }
}

function renameLayer(undoName, redoName) {
    var _undoName = undoName
    var _redoName = redoName
    return {
        name: qsTr("Rename Layer"),
        undo: function() {
            layerModel.setProperty(currentLayerIndex, "name", _undoName)
        },
        redo: function() {
            layerModel.setProperty(currentLayerIndex, "name", _redoName)
        }
    }
}
