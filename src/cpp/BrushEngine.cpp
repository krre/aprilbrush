#include "BrushEngine.h"
#include <QtGui>

void BrushEngine::paint(const QPointF& point, float pressure) {
    QPainter painter(_eraser > 50 ? canvasItem->pixmap() : canvasBuffer->pixmap());
    painter.setRenderHint(QPainter::Antialiasing, true);
    painter.setPen(Qt::NoPen);
    if (_eraser > 50) {
        painter.setCompositionMode(QPainter::CompositionMode_DestinationOut);
    }

    _color.setAlpha(qRound(255 * _flow / 100.0));
    QColor pressureColor = _color;
    pressureColor.setAlpha(qRound(_color.alpha() * pressure));
    QColor alphaColor = _color;
    alphaColor.setAlpha(0);

    QRadialGradient radialGradient;
    radialGradient.setRadius(_size / 2.0);
    radialGradient.setColorAt(0, pressureColor);
    radialGradient.setColorAt(1, alphaColor);
    radialGradient.setColorAt(_hardness / 100.0, pressureColor);
    painter.setBrush(QBrush(radialGradient));

    if (startPoint.isNull()) {
        startPoint = QPointF(point);
        lastPoint = QPointF(point);
        topleft = QPoint(0, 0);
        bottomright = QPoint(canvasBuffer->pixmap()->width(), canvasBuffer->pixmap()->height());
        paintDab(point, painter);
    } else {
        qreal length = qSqrt(qPow(lastPoint.x() - point.x(), 2) + qPow(lastPoint.y() - point.y(), 2));
        qreal delta = _size * _spacing / 2 / 100.0;

        if (length >= delta) {
            int dabs = qRound(length / delta);
            qreal angle = qAtan2(point.x() - lastPoint.x(), point.y() - lastPoint.y());
            qreal deltaX = delta * qSin(angle);
            qreal deltaY = delta * qCos(angle);

            QPointF betweenPoint;
            for (int i = 1; i <= dabs; i++) {
                qreal x = lastPoint.x() + deltaX * i +
                        (10000 - qrand() % 20000) / 10000.0 * _size * _jitter / 100;
                qreal y = lastPoint.y() + deltaY * i +
                        (10000 - qrand() % 20000) / 10000.0 * _size * _jitter / 100;
                betweenPoint = QPointF(x, y);
                paintDab(betweenPoint, painter);

            }
            lastPoint = betweenPoint;
        }
    }
}

void BrushEngine::setCanvasItem(CanvasItem *canvasItem) {
    this->canvasItem = canvasItem;
    _undoImage = canvasItem->image();
}

void BrushEngine::setColor(QColor color) {
    if (_color == color) return;
    _color = color;
    emit colorChanged(color);
}

void BrushEngine::setSize(int size) {
    if (_size == size) return;
    _size = size;
    emit sizeChanged(size);
}

void BrushEngine::setHardness(int hardness) {
    if (_hardness == hardness) return;
    _hardness = hardness;
    emit hardnessChanged(hardness);
}

void BrushEngine::setOpacity(int opacity) {
    if (_opacity == opacity) return;
    _opacity = opacity;
    emit opacityChanged(opacity);
}

void BrushEngine::setRoundness(int roundness) {
    if (_roundness == roundness) return;
    _roundness = roundness;
    emit roundnessChanged(roundness);
}

void BrushEngine::setAngle(int angle) {
    if (_angle == angle) return;
    _angle = angle;
    emit angleChanged(angle);
}

void BrushEngine::setSpacing(int spacing) {
    if (_spacing == spacing) return;
    _spacing = spacing;
    emit spacingChanged(spacing);
}

void BrushEngine::setJitter(int jitter) {
    if (_jitter == jitter) return;
    _jitter = jitter;
    emit jitterChanged(jitter);
}

void BrushEngine::setIsTouch(bool isTouch) {
    if (_isTouch == isTouch) return;
    _isTouch = isTouch;
    if (isTouch) {
        startPoint = QPointF();
    } else {
        _undoImage = canvasItem->image(topleft, bottomright);

        QPainter painter(canvasItem->pixmap());
        painter.setOpacity(_opacity / 100.0);
        painter.drawPixmap(0, 0, *canvasBuffer->pixmap());
        canvasBuffer->pixmap()->fill(Qt::transparent);
        canvasItem->update();
        canvasBuffer->update();

        _redoImage = canvasItem->image(topleft, bottomright);

        // Correct corner positions on brush size
        topleft.setX(topleft.x() - _size);
        topleft.setY(topleft.y() - _size);
        bottomright.setX(bottomright.x() + _size);
        bottomright.setY(bottomright.y() + _size);

        topleft.setX(qMax(0, topleft.x()));
        topleft.setY(qMax(0, topleft.y()));
        bottomright.setX(qMin(canvasBuffer->pixmap()->width(), bottomright.x()));
        bottomright.setY(qMin(canvasBuffer->pixmap()->height(), bottomright.y()));
    }
    emit isTouchChanged(isTouch);
}

void BrushEngine::setFlow(int flow) {
    if (_flow == flow) return;
    _flow = flow;
    emit flowChanged(flow);
}

void BrushEngine::setEraser(int eraser) {
    if (_eraser == eraser) return;
    _eraser = eraser;
    emit eraserChanged(eraser);
}

void BrushEngine::paintDab(const QPointF& point, QPainter& painter) {
    painter.save();
    painter.translate(point);
    painter.rotate(_angle);
    painter.scale(1, _roundness / 100.0);
    QRect rect(-_size / 2.0, -_size / 2.0, _size, _size);
    painter.drawEllipse(rect);
    painter.restore();
    rect.moveTo(point.x() - _size / 2, point.y() - _size / 2);
    if (_eraser > 50) {
        canvasItem->update(rect);
    } else {
        canvasBuffer->update(rect);
    }

    // Detect a min and max corner positions
    bottomright.setX(qMax(bottomright.x(), qRound(point.x())));
    bottomright.setY(qMax(bottomright.y(), qRound(point.y())));
    topleft.setX(qMin(topleft.x(), qRound(point.x())));
    topleft.setY(qMin(topleft.y(), qRound(point.y())));
}
