#include "BrushEngine.h"
#include "CanvasItem.h"
#include <QtGui>

void BrushEngine::paint(const QPointF& point, float pressure) {
    QPainter painter(_eraser > 50 ? _canvasItem->pixmap() : _canvasBuffer->pixmap());
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

    if (_startPoint.isNull()) {
        _startPoint = QPointF(point);
        _lastPoint = QPointF(point);
        _topleft = QPoint(0, 0);
        _bottomright = QPoint(_canvasBuffer->pixmap()->width(), _canvasBuffer->pixmap()->height());
        paintDab(point, painter);
    } else {
        qreal length = qSqrt(qPow(_lastPoint.x() - point.x(), 2) + qPow(_lastPoint.y() - point.y(), 2));
        qreal delta = _size * _spacing / 2 / 100.0;

        if (length >= delta) {
            int dabs = qRound(length / delta);
            qreal angle = qAtan2(point.x() - _lastPoint.x(), point.y() - _lastPoint.y());
            qreal deltaX = delta * qSin(angle);
            qreal deltaY = delta * qCos(angle);

            QPointF betweenPoint;
            for (int i = 1; i <= dabs; i++) {
                qreal x = _lastPoint.x() + deltaX * i +
                        (10000 - qrand() % 20000) / 10000.0 * _size * _jitter / 100;
                qreal y = _lastPoint.y() + deltaY * i +
                        (10000 - qrand() % 20000) / 10000.0 * _size * _jitter / 100;
                betweenPoint = QPointF(x, y);
                paintDab(betweenPoint, painter);

            }
            _lastPoint = betweenPoint;
        }
    }
}

void BrushEngine::setCanvasItem(CanvasItem *canvasItem) {
    this->_canvasItem = canvasItem;
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
        _startPoint = QPointF();
    } else {
        _undoImage = _canvasItem->image(_topleft, _bottomright);

        QPainter painter(_canvasItem->pixmap());
        painter.setOpacity(_opacity / 100.0);
        painter.drawPixmap(0, 0, *_canvasBuffer->pixmap());
        _canvasBuffer->pixmap()->fill(Qt::transparent);
        _canvasItem->update();
        _canvasBuffer->update();

        _redoImage = _canvasItem->image(_topleft, _bottomright);

        // Correct corner positions on brush size
        _topleft.setX(_topleft.x() - _size);
        _topleft.setY(_topleft.y() - _size);
        _bottomright.setX(_bottomright.x() + _size);
        _bottomright.setY(_bottomright.y() + _size);

        _topleft.setX(qMax(0, _topleft.x()));
        _topleft.setY(qMax(0, _topleft.y()));
        _bottomright.setX(qMin(_canvasBuffer->pixmap()->width(), _bottomright.x()));
        _bottomright.setY(qMin(_canvasBuffer->pixmap()->height(), _bottomright.y()));
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
        _canvasItem->update(rect);
    } else {
        _canvasBuffer->update(rect);
    }

    // Detect a min and max corner positions
    _bottomright.setX(qMax(_bottomright.x(), qRound(point.x())));
    _bottomright.setY(qMax(_bottomright.y(), qRound(point.y())));
    _topleft.setX(qMin(_topleft.x(), qRound(point.x())));
    _topleft.setY(qMin(_topleft.y(), qRound(point.y())));
}
