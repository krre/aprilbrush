#include "BrushEngine.h"
#include "CanvasItem.h"
#include <QtGui>

void BrushEngine::paint(const QPointF& point, float pressure) {
    QPainter painter(eraser > 50 ? canvasItem->getPixmap() : canvasBuffer->getPixmap());
    painter.setRenderHint(QPainter::Antialiasing, true);
    painter.setPen(Qt::NoPen);
    if (eraser > 50) {
        painter.setCompositionMode(QPainter::CompositionMode_DestinationOut);
    }

    color.setAlpha(qRound(255 * flow / 100.0));
    QColor pressureColor = color;
    pressureColor.setAlpha(qRound(color.alpha() * pressure));
    QColor alphaColor = color;
    alphaColor.setAlpha(0);

    QRadialGradient radialGradient;
    radialGradient.setRadius(size / 2.0);
    radialGradient.setColorAt(0, pressureColor);
    radialGradient.setColorAt(1, alphaColor);
    radialGradient.setColorAt(hardness / 100.0, pressureColor);
    painter.setBrush(QBrush(radialGradient));

    if (startPoint.isNull()) {
        startPoint = QPointF(point);
        lastPoint = QPointF(point);
        topleft = QPoint(0, 0);
        bottomright = QPoint(canvasBuffer->getPixmap()->width(), canvasBuffer->getPixmap()->height());
        paintDab(point, painter);
    } else {
        qreal length = qSqrt(qPow(lastPoint.x() - point.x(), 2) + qPow(lastPoint.y() - point.y(), 2));
        qreal delta = size * spacing / 2 / 100.0;

        if (length >= delta) {
            int dabs = qRound(length / delta);
            qreal angle = qAtan2(point.x() - lastPoint.x(), point.y() - lastPoint.y());
            qreal deltaX = delta * qSin(angle);
            qreal deltaY = delta * qCos(angle);

            QPointF betweenPoint;
            for (int i = 1; i <= dabs; i++) {
                qreal x = lastPoint.x() + deltaX * i +
                        (10000 - qrand() % 20000) / 10000.0 * size * jitter / 100;
                qreal y = lastPoint.y() + deltaY * i +
                        (10000 - qrand() % 20000) / 10000.0 * size * jitter / 100;
                betweenPoint = QPointF(x, y);
                paintDab(betweenPoint, painter);

            }
            lastPoint = betweenPoint;
        }
    }
}

void BrushEngine::setCanvasItem(CanvasItem* canvasItem) {
    this->canvasItem = canvasItem;
    undoImage = canvasItem->getImage();
}

void BrushEngine::setCanvasBuffer(CanvasItem* canvasBuffer) {
    this->canvasBuffer = canvasBuffer;
}

void BrushEngine::setColor(QColor color) {
    if (this->color == color) return;
    this->color = color;
    emit colorChanged(color);
}

void BrushEngine::setSize(int size) {
    if (this->size == size) return;
    this->size = size;
    emit sizeChanged(size);
}

void BrushEngine::setHardness(int hardness) {
    if (this->hardness == hardness) return;
    this->hardness = hardness;
    emit hardnessChanged(hardness);
}

void BrushEngine::setOpacity(int opacity) {
    if (this->opacity == opacity) return;
    this->opacity = opacity;
    emit opacityChanged(opacity);
}

void BrushEngine::setRoundness(int roundness) {
    if (this->roundness == roundness) return;
    this->roundness = roundness;
    emit roundnessChanged(roundness);
}

void BrushEngine::setAngle(int angle) {
    if (this->angle == angle) return;
    this->angle = angle;
    emit angleChanged(angle);
}

void BrushEngine::setSpacing(int spacing) {
    if (this->spacing == spacing) return;
    this->spacing = spacing;
    emit spacingChanged(spacing);
}

void BrushEngine::setJitter(int jitter) {
    if (this->jitter == jitter) return;
    this->jitter = jitter;
    emit jitterChanged(jitter);
}

void BrushEngine::setIsTouch(bool isTouch) {
    if (this->isTouch == isTouch) return;
    this->isTouch = isTouch;

    if (isTouch) {
        startPoint = QPointF();
    } else {
        undoImage = canvasItem->getImage(topleft, bottomright);

        QPainter painter(canvasItem->getPixmap());
        painter.setOpacity(opacity / 100.0);
        painter.drawPixmap(0, 0, *canvasBuffer->getPixmap());
        canvasBuffer->getPixmap()->fill(Qt::transparent);
        canvasItem->update();
        canvasBuffer->update();

        redoImage = canvasItem->getImage(topleft, bottomright);

        // Correct corner positions on brush size
        topleft.setX(topleft.x() - size);
        topleft.setY(topleft.y() - size);
        bottomright.setX(bottomright.x() + size);
        bottomright.setY(bottomright.y() + size);

        topleft.setX(qMax(0, topleft.x()));
        topleft.setY(qMax(0, topleft.y()));
        bottomright.setX(qMin(canvasBuffer->getPixmap()->width(), bottomright.x()));
        bottomright.setY(qMin(canvasBuffer->getPixmap()->height(), bottomright.y()));
    }
    emit isTouchChanged(isTouch);
}

void BrushEngine::setFlow(int flow) {
    if (this->flow == flow) return;
    this->flow = flow;
    emit flowChanged(flow);
}

void BrushEngine::setEraser(int eraser) {
    if (this->eraser == eraser) return;
    this->eraser = eraser;
    emit eraserChanged(eraser);
}

void BrushEngine::paintDab(const QPointF& point, QPainter& painter) {
    painter.save();
    painter.translate(point);
    painter.rotate(angle);
    painter.scale(1, roundness / 100.0);
    QRect rect(-size / 2.0, -size / 2.0, size, size);
    painter.drawEllipse(rect);
    painter.restore();
    rect.moveTo(point.x() - size / 2, point.y() - size / 2);
    if (eraser > 50) {
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
