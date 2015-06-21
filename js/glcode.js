var canvas3d
var gl
var isLogEnabled = false

function log(message) {
    if (isLogEnabled) {
        print(message)
    }
}

function initializeGL(canvas) {
    canvas3d = canvas
    try {
        gl = canvas.getContext("canvas3d")
        gl.clearColor(1.0, 1.0, 1.0, 1.0)
    } catch(e) {
        print("initializeGL FAILURE!")
        print(""+e)
        print(""+e.message)
    }
}

function paintGL(canvas) {
    gl.clear(gl.COLOR_BUFFER_BIT)
}

