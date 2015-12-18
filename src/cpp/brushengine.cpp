#include "brushengine.h"

void BrushEngine::paint(const QPointF& point, float pressure)
{
    QPainter painter(m_eraser > 50 ? canvasItem->pixmap() : canvasBuffer->pixmap());
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

void BrushEngine::setColor(QColor color)
{
    if (m_color == color) return;
    m_color = color;
    emit colorChanged(color);
}

void BrushEngine::setSize(int size)
{
    if (m_size == size) return;
    m_size = size;
    emit sizeChanged(size);
}

void BrushEngine::setHardness(int hardness)
{
    if (m_hardness == hardness) return;
    m_hardness = hardness;
    emit hardnessChanged(hardness);
}

void BrushEngine::setOpacity(int opacity)
{
    if (m_opacity == opacity) return;
    m_opacity = opacity;
    emit opacityChanged(opacity);
}

void BrushEngine::setRoundness(int roundness)
{
    if (m_roundness == roundness) return;
    m_roundness = roundness;
    emit roundnessChanged(roundness);
}

void BrushEngine::setAngle(int angle)
{
    if (m_angle == angle) return;
    m_angle = angle;
    emit angleChanged(angle);
}

void BrushEngine::setSpacing(int spacing)
{
    if (m_spacing == spacing) return;
    m_spacing = spacing;
    emit spacingChanged(spacing);
}

void BrushEngine::setJitter(int jitter)
{
    if (m_jitter == jitter) return;
    m_jitter = jitter;
    emit jitterChanged(jitter);
}

void BrushEngine::setIsTouch(bool isTouch)
{
    if (m_isTouch == isTouch) return;
    m_isTouch = isTouch;
    if (isTouch) {
        m_undoBase64Image = canvasItem->base64Image();
    } else {
        QPainter painter(canvasItem->pixmap());
        painter.setOpacity(m_opacity / 100.0);
        painter.drawPixmap(0, 0, *canvasBuffer->pixmap());
        canvasBuffer->pixmap()->fill(Qt::transparent);
        canvasItem->update();
        canvasBuffer->update();

        m_redoBase64Image = canvasItem->base64Image();

        startPoint = QPointF();
    }
    emit isTouchChanged(isTouch);
}

void BrushEngine::setFlow(int flow)
{
    if (m_flow == flow) return;
    m_flow = flow;
    emit flowChanged(flow);
}

void BrushEngine::setEraser(int eraser)
{
    if (m_eraser == eraser) return;
    m_eraser = eraser;
    emit eraserChanged(eraser);
}

void BrushEngine::paintDab(const QPointF& point, QPainter& painter)
{
    painter.save();
    painter.translate(point);
    painter.rotate(m_angle);
    painter.scale(1, m_roundness / 100.0);
    QRect rect(-m_size / 2.0, -m_size / 2.0, m_size, m_size);
    painter.drawEllipse(rect);
    painter.restore();
    rect.moveTo(point.x() - m_size / 2, point.y() - m_size / 2);
    if (m_eraser > 50) {
        canvasItem->update(rect);
    } else {
        canvasBuffer->update(rect);
    }
}
