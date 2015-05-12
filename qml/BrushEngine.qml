import QtQuick 2.4

Item {
    id: root
    property bool isFirstPoint: false
    property Canvas canvas
    property real deltaDab: Math.max(brushSettings.spacing / 100 * brushSettings.size, 1)
    property var points: []
    property bool linearMode: false
    property bool isBezier: true // change only for testing
    property point lastDrawPoint
    property point controlPoint
    property point grabPoint
    property point startPoint
    property point endPoint
    property point betweenPoint

    function setTouch(isTouch, canvas) {
        if (isTouch) {
            root.canvas = canvas
            isFirstPoint = true
        }
    }

    function paint(point, pressure) {
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
                    curvePoint = !(controlPoint.x === -1 && controlPoint.y === -1)? linearCurve(startPoint, endPoint, t) : bezierCurve(startPoint, endPoint, controlPoint, t)
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
//        QPainter painter(canvas->image());
//        painter.setRenderHint(QPainter::Antialiasing, true);
//        painter.setPen(Qt::NoPen);
//        painter.setBrush(QBrush(m_color));
//        painter.setOpacity(m_opacity / 100.0 * pressure);
//        QRectF rect;
//        if (m_size > 1) {
//            rect = QRectF(QPointF(point.x() - m_size / 2.0, point.y() - m_size / 2.0), QSizeF(m_size, m_size));
//            painter.drawEllipse(rect);
//        } else {
//            rect = QRectF(point.x() - 0.5, point.y() - 0.5, 1, 1);
//            painter.drawRect(rect);
//        }
//        painted(rect);

        var ctx = canvas.getContext("2d")
        ctx.save()
        ctx.globalAlpha = pressure
        var size = brushSettings.size
        var x = point.x - size / 2 + size * brushSettings.jitter / 100 * (1 - 2 * Math.random())
        var y = point.y - size / 2 + size * brushSettings.jitter / 100 * (1 - 2 * Math.random())

//        if (x < startPos.x) { startPos.x = Math.min(0, x) }
//        if (y < startPos.y) { startPos.y = Math.min(0, y) }
//        if (x > finalPos.x) { finalPos.x = Math.max(x, imageSize.width) }
//        if (y > finalPos.y) { finalPos.y = Math.max(y, imageSize.height) }

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
        width: brushSettings.size
        height: brushSettings.size
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
            ctx.rotate(brushSettings.angle / 180 * Math.PI)
            ctx.scale(1.0, brushSettings.roundness / 100)
            ctx.translate(-originX, -originY)

            var color = Qt.rgba(colorPicker.color.r, colorPicker.color.g, colorPicker.color.b, brushSettings.flow / 100)
            var gradient = ctx.createRadialGradient(width / 2, height / 2, 0, width / 2, height / 2, width / 2)
            gradient.addColorStop(0, color)
            gradient.addColorStop(brushSettings.hardness / 100, color)
            gradient.addColorStop(1, Qt.rgba(colorPicker.color.r, colorPicker.color.g, colorPicker.color.b, brushSettings.hardness / 100 < 1 ? 0 : brushSettings.flow / 100))

            ctx.ellipse(0, 0, width, width)
            ctx.fillStyle = gradient
            ctx.fill()

            ctx.restore()
        }
    }
}

