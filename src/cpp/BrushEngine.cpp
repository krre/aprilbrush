#include "BrushEngine.h"
#include "CanvasItem.h"
#include <QtGui>

namespace AprilBrush {

void BrushEngine::paint(const QPointF& point, float pressure) {
    QPainter painter(m_eraser > 50 ? m_canvasItem->pixmap() : m_canvasBuffer->pixmap());
    painter.setRenderHint(QPainter::Antialiasing, true);
    painter.setPen(Qt::NoPen);
    if (m_eraser > 50) {
        painter.setCompositionMode(QPainter::CompositionMode_DestinationOut);
    }

    m_color.setAlpha(qRound(255 * m_flow / 100.0));
    QColor pressureColor = m_color;
    pressureColor.setAlpha(qRound(m_color.alpha() * pressure));
    QColor alphaColor = m_color;
    alphaColor.setAlpha(0);

    QRadialGradient radialGradient;
    radialGradient.setRadius(m_size / 2.0);
    radialGradient.setColorAt(0, pressureColor);
    radialGradient.setColorAt(1, alphaColor);
    radialGradient.setColorAt(m_hardness / 100.0, pressureColor);
    painter.setBrush(QBrush(radialGradient));

    if (startPoint.isNull()) {
        startPoint = QPointF(point);
        lastPoint = QPointF(point);
        topleft = QPoint(0, 0);
        bottomright = QPoint(m_canvasBuffer->pixmap()->width(), m_canvasBuffer->pixmap()->height());
        paintDab(point, painter);
    } else {
        qreal length = qSqrt(qPow(lastPoint.x() - point.x(), 2) + qPow(lastPoint.y() - point.y(), 2));
        qreal delta = m_size * m_spacing / 2 / 100.0;

        if (length >= delta) {
            int dabs = qRound(length / delta);
            qreal angle = qAtan2(point.x() - lastPoint.x(), point.y() - lastPoint.y());
            qreal deltaX = delta * qSin(angle);
            qreal deltaY = delta * qCos(angle);

            QPointF betweenPoint;
            for (int i = 1; i <= dabs; i++) {
                qreal x = lastPoint.x() + deltaX * i +
                        (10000 - qrand() % 20000) / 10000.0 * m_size * m_jitter / 100;
                qreal y = lastPoint.y() + deltaY * i +
                        (10000 - qrand() % 20000) / 10000.0 * m_size * m_jitter / 100;
                betweenPoint = QPointF(x, y);
                paintDab(betweenPoint, painter);

            }
            lastPoint = betweenPoint;
        }
    }
}

void BrushEngine::setCanvasItem(CanvasItem* canvasItem) {
    this->m_canvasItem = canvasItem;
    m_undoImage = canvasItem->image();
}

void BrushEngine::setColor(QColor color) {
    if (m_color == color) return;
    m_color = color;
    emit colorChanged(color);
}

void BrushEngine::setSize(int size) {
    if (m_size == size) return;
    m_size = size;
    emit sizeChanged(size);
}

void BrushEngine::setHardness(int hardness) {
    if (m_hardness == hardness) return;
    m_hardness = hardness;
    emit hardnessChanged(hardness);
}

void BrushEngine::setOpacity(int opacity) {
    if (m_opacity == opacity) return;
    m_opacity = opacity;
    emit opacityChanged(opacity);
}

void BrushEngine::setRoundness(int roundness) {
    if (m_roundness == roundness) return;
    m_roundness = roundness;
    emit roundnessChanged(roundness);
}

void BrushEngine::setAngle(int angle) {
    if (m_angle == angle) return;
    m_angle = angle;
    emit angleChanged(angle);
}

void BrushEngine::setSpacing(int spacing) {
    if (m_spacing == spacing) return;
    m_spacing = spacing;
    emit spacingChanged(spacing);
}

void BrushEngine::setJitter(int jitter) {
    if (m_jitter == jitter) return;
    m_jitter = jitter;
    emit jitterChanged(jitter);
}

void BrushEngine::setIsTouch(bool isTouch) {
    if (m_isTouch == isTouch) return;
    m_isTouch = isTouch;
    if (isTouch) {
        startPoint = QPointF();
    } else {
        m_undoImage = m_canvasItem->image(topleft, bottomright);

        QPainter painter(m_canvasItem->pixmap());
        painter.setOpacity(m_opacity / 100.0);
        painter.drawPixmap(0, 0, *m_canvasBuffer->pixmap());
        m_canvasBuffer->pixmap()->fill(Qt::transparent);
        m_canvasItem->update();
        m_canvasBuffer->update();

        m_redoImage = m_canvasItem->image(topleft, bottomright);

        // Correct corner positions on brush size
        topleft.setX(topleft.x() - m_size);
        topleft.setY(topleft.y() - m_size);
        bottomright.setX(bottomright.x() + m_size);
        bottomright.setY(bottomright.y() + m_size);

        topleft.setX(qMax(0, topleft.x()));
        topleft.setY(qMax(0, topleft.y()));
        bottomright.setX(qMin(m_canvasBuffer->pixmap()->width(), bottomright.x()));
        bottomright.setY(qMin(m_canvasBuffer->pixmap()->height(), bottomright.y()));
    }
    emit isTouchChanged(isTouch);
}

void BrushEngine::setFlow(int flow) {
    if (m_flow == flow) return;
    m_flow = flow;
    emit flowChanged(flow);
}

void BrushEngine::setEraser(int eraser) {
    if (m_eraser == eraser) return;
    m_eraser = eraser;
    emit eraserChanged(eraser);
}

void BrushEngine::paintDab(const QPointF& point, QPainter& painter) {
    painter.save();
    painter.translate(point);
    painter.rotate(m_angle);
    painter.scale(1, m_roundness / 100.0);
    QRect rect(-m_size / 2.0, -m_size / 2.0, m_size, m_size);
    painter.drawEllipse(rect);
    painter.restore();
    rect.moveTo(point.x() - m_size / 2, point.y() - m_size / 2);
    if (m_eraser > 50) {
        m_canvasItem->update(rect);
    } else {
        m_canvasBuffer->update(rect);
    }

    // Detect a min and max corner positions
    bottomright.setX(qMax(bottomright.x(), qRound(point.x())));
    bottomright.setY(qMax(bottomright.y(), qRound(point.y())));
    topleft.setX(qMin(topleft.x(), qRound(point.x())));
    topleft.setY(qMin(topleft.y(), qRound(point.y())));
}

} // AprilBrush
