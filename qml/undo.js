function start(pixmap) {
    return {
        name: "Start",
        undo: function() {
            console.log("undo-start");
        },
        redo: function() {
            console.log("redo-start");
        }
    }
}

function paint(pixmap) {
    return {
        name: "Paint",
        undo: function() {
            console.log("undo-paint");
        },
        redo: function() {
            console.log("redo-paint");
        }
    }
}

function clear(pixmap) {
    return {
        name: "Clear",
        undo: function() {
            console.log("undo-clear");
        },
        redo: function() {
            console.log("redo-clear");
        }
    }
}

function addLayer(pixmap) {
    return {
        name: "Add Layer",
        undo: function() {
            console.log("undo-add-layer");
        },
        redo: function() {
            console.log("redo-add-layer");
        }
    }
}

function deleteLayer(pixmap) {
    return {
        name: "Delete Layer",
        undo: function() {
            console.log("undo-delete-layer");
        },
        redo: function() {
            console.log("redo-delete-layer");
        }
    }
}

function raiseLayer(pixmap) {
    return {
        name: "Raise Layer",
        undo: function() {
            console.log("undo-raise-layer");
        },
        redo: function() {
            console.log("redo-raise-layer");
        }
    }
}

function lowerLayer(pixmap) {
    return {
        name: "Lower Layer",
        undo: function() {
            console.log("undo-lower-layer");
        },
        redo: function() {
            console.log("redo-lower-layer");
        }
    }
}

function renameLayer(pixmap) {
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

function cloneLayer(pixmap) {
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
