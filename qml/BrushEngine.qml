import QtQuick 2.4

Item {
    id: root
    property bool isFirstPoint: false
    property Canvas canvas: canvasArea.canvas
    property real deltaDab: Math.max(spacing / 100 * size, 1)
    property var points: []
    property bool isBezier: true // change only for testing
    property point lastDrawPoint
    property point controlPoint
    property point startPoint
    property point endPoint
    property point betweenPoint
    property point maxPoint: Qt.point(0, 0)
    property point minPoint: Qt.point(imageSize.width, imageSize.height)

    property color color: colorPicker.color
    property int size: brushSettings.size
    property int opaque: brushSettings.opaque
    property int flow: brushSettings.flow
    property int hardness: brushSettings.hardness
    property int spacing: brushSettings.spacing
    property int roundness: brushSettings.roundness
    property int angle: brushSettings.angle
    property int jitter: brushSettings.jitter
    property int eraser: brushSettings.eraser

    onColorChanged: dab.requestPaint()
    onSizeChanged: dab.requestPaint()
    onOpacityChanged: dab.requestPaint()
    onFlowChanged: dab.requestPaint()
    onHardnessChanged: dab.requestPaint()
    onSpacingChanged: dab.requestPaint()
    onAngleChanged: dab.requestPaint()
    onJitterChanged: dab.requestPaint()
    onEraserChanged: dab.requestPaint()

    function setTouch(isTouch) {
        if (isTouch) {
            isFirstPoint = true
        }
    }

    function paint(point, pressure) {
        if (!canvas.enabled) return // layer is locked
        if (isFirstPoint) {
            paintDab(point, pressure)
            points = []
            points.push(point)
            lastDrawPoint = point
            controlPoint = Qt.point(-1, -1)
            isFirstPoint = false
        } else {
            paintDab(point, pressure)
            startPoint = lastDrawPoint
            var deltaPoint = Math.sqrt(Math.pow(startPoint.x - point.x, 2) + Math.pow(startPoint.y - point.y, 2))
            var numDabs = Math.floor(deltaPoint / deltaDab)
            if (numDabs >= 1) {
                if (points.length === 1 || numDabs < 3 || !isBezier) {
                    endPoint = point
                } else {
                    controlPoint = points[points.length - 1]
                    endPoint.x = (controlPoint.x + point.x) / 2
                    endPoint.y = (controlPoint.y + point.y) / 2
                }
                var deltaT = 1.0 / numDabs
                betweenPoint = startPoint
                var t = deltaT
                var diff = 0
                var curvePoint
                while (t > 0 && t <= 1) {
                    curvePoint = !(controlPoint.x === -1 && controlPoint.y === -1) ? linearCurve(startPoint, endPoint, t) : bezierCurve(startPoint, endPoint, controlPoint, t)
                    deltaPoint = Math.sqrt(Math.pow(curvePoint.x - betweenPoint.x, 2) + Math.pow(curvePoint.y - betweenPoint.y, 2))
                    if (diff && Math.abs(deltaPoint - deltaDab) > Math.abs(diff)) { break; } // check on bezier loop
                    diff = deltaPoint - deltaDab
                    if (Math.abs(diff) <= 0.5) {
                        paintDab(curvePoint, pressure)
                        diff = 0
                        betweenPoint = curvePoint
                        t += deltaT
                    } else {
                        t -= diff / deltaDab * deltaT
                    }
                }

                points.push(point)
                lastDrawPoint = betweenPoint
                controlPoint = Qt.point(-1, -1)
            }
        }
    }

    function paintDab(point, pressure) {
        var ctx = canvas.getContext("2d")
        ctx.save()
        ctx.globalAlpha = pressure
        var x = point.x - size / 2 + size * jitter / 100 * (1 - 2 * Math.random())
        var y = point.y - size / 2 + size * jitter / 100 * (1 - 2 * Math.random())

        if (x < minPoint.x) minPoint.x = Math.min(0, x)
        if (y < minPoint.y) minPoint.y = Math.min(0, y)
        if (x > maxPoint.x) maxPoint.x = Math.max(x, imageSize.width)
        if (y > maxPoint.y) maxPoint.y = Math.max(x, imageSize.height)

        ctx.drawImage(dab, x, y)
        ctx.restore()
        canvas.markDirty(x, y, dab.width, dab.height)
    }

    function linearCurve(start, end, t) {
        var x = (1 - t) * start.x + t * end.x
        var y = (1 - t) * start.y + t * end.y
        return Qt.point(x, y)
    }

    function bezierCurve(start, end, control, t) {
        var x = Math.pow((1 - t), 2) * start.x + 2 * t * (1 - t) * control.x + t * t * end.x
        var y = Math.pow((1 - t), 2) * start.y + 2 * t * (1 - t) * control.y + t * t * end.y
        return Qt.point(x, y)
    }

    Canvas {
        id: dab
        width: size
        height: size
        visible: false
        antialiasing: true
        smooth: false

        onAvailableChanged: requestPaint()

        onPaint: {
            var ctx = getContext("2d")
            ctx.save()
            ctx.clearRect(0, 0, width, height)

            var originX = width / 2
            var originY = width / 2

            ctx.translate(originX, originY)
            ctx.rotate(angle / 180 * Math.PI)
            ctx.scale(1.0, roundness / 100)
            ctx.translate(-originX, -originY)

            var color = Qt.rgba(root.color.r, root.color.g, root.color.b, flow / 100)
            var gradient = ctx.createRadialGradient(width / 2, height / 2, 0, width / 2, height / 2, width / 2)
            gradient.addColorStop(0, color)
            gradient.addColorStop(hardness / 100, color)
            gradient.addColorStop(1, Qt.rgba(root.color.r, root.color.g, root.color.b, hardness / 100 < 1 ? 0 : flow / 100))

            ctx.ellipse(0, 0, width, width)
            ctx.fillStyle = gradient
            ctx.fill()

            ctx.restore()
        }
    }
}

