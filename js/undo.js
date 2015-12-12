function start() {
    return {
        name: qsTr("Start"),
        undo: function() {},
        redo: function() {}
    }
}

function paint(startPos, undoArea, redoArea, alpha, isEraser) {
    var _startPos = Qt.point(startPos.x, startPos.y)
    var _undoArea = undoArea
    var _redoArea = redoArea
    var _alpha = alpha
    var _isHistory = false
    var _isEraser = isEraser

    return {
        name: isEraser ? qsTr("Eraser") : qsTr("Brush"),
        undo: function() {
            canvasArea.canvas.getContext("2d").clearRect(_startPos.x, _startPos.y,  _undoArea.width, _undoArea.height)
            canvasArea.canvas.getContext("2d").drawImage(_undoArea, _startPos.x, _startPos.y)
            canvasArea.canvas.requestPaint()
        },
        redo: function() {
            if (_isEraser && !_isHistory) {
                _isHistory = true
            } else {
                var ctx = canvas.getContext("2d")
                ctx.save()
                if (_isEraser) {
                    ctx.clearRect(_startPos.x, _startPos.y,  _redoArea.width, _redoArea.height)
                }
                ctx.globalAlpha = _isEraser ? 1.0 : _alpha
                ctx.drawImage(_redoArea, _startPos.x, _startPos.y)
                ctx.restore()
                canvasArea.canvas.requestPaint()
            }
        }
    }
}

function clearLayer() {
    var _undoArea = canvasArea.canvas.getContext("2d").getImageData(0, 0, imageSize.width, imageSize.height)
    return {
        name: qsTr("Clear"),
        undo: function() {
            canvasArea.canvas.getContext("2d").drawImage(_undoArea, 0, 0)
            canvasArea.canvas.requestPaint()
        },
        redo: function() {
            canvasArea.canvas.clear()
        }
    }
}

function changeLayer(undoIndex, redoIndex) {
    return {
        name: qsTr("Change Layer"),
        undo: function() {
            layerManager.layerView.currentIndex = undoIndex
        },
        redo: function() {
            layerManager.layerView.currentIndex = redoIndex
        }
    }
}

function addLayer(name) {
    return {
        name: qsTr("Add Layer"),
        undo: function() {
            layerModel.remove(layerView.currentIndex)
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
            layerManager.layerView.currentIndex = _index
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
    var _indexUp = layerView.currentIndex
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
            layerModel.remove(layerView.currentIndex)
        },
        redo: function() {
            var _name = layerModel.get(layerView.currentIndex).name
            var _duplicateArea = canvasArea.canvas.getContext("2d").getImageData(0, 0, imageSize.width, imageSize.height)
            var layerObj = layerManager.defaultLayer()
            layerObj.name = _name
            layerModel.insert(currentLayerIndex, layerObj)
            layerManager.layerView.currentIndex = currentLayerIndex
            layerModel.get(currentLayerIndex).canvas.onReady.connect(function() {
                layerModel.get(currentLayerIndex).canvas.getContext("2d").drawImage(_duplicateArea, 0, 0)
                layerModel.get(currentLayerIndex).canvas.requestPaint()
            })
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
    var _index = index
    var _isVisible = layerModel.get(_index).isVisible
    return {
        name: _isVisible ? qsTr("Layer Unvisible") : qsTr("Layer Visible"),
        undo: function() {
            layerModel.setProperty(_index, "isVisible", _isVisible)
        },
        redo: function() {
            layerModel.setProperty(_index, "isVisible", !_isVisible)
        }
    }
}

function changeIsLockLayer(index) {
    var _index = index
    var _isLock = layerModel.get(_index).isLock
    return {
        name: _isLock ? qsTr("Layer Unlock") : qsTr("Layer Lock"),
        undo: function() {

            layerModel.setProperty(_index, "isLock", _isLock)
        },
        redo: function() {
            layerModel.setProperty(_index, "isLock", !_isLock)
        }
    }
}
