#include "BrushEngine.h"
#include "Layer.h"
#include <QtGui>

void BrushEngine::paint(const QPointF& point, float pressure) {
    QPainter painter(m_eraser > 50 ? m_layer->pixmap() : m_layerBuffer->pixmap());
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
        bottomright = QPoint(m_layerBuffer->pixmap()->width(), m_layerBuffer->pixmap()->height());
        paintDab(point, painter);
    } else {
        qreal length = qSqrt(qPow(lastPoint.x() - point.x(), 2) + qPow(lastPoint.y() - point.y(), 2));
        qreal delta = m_size * m_spacing / 2.0 / 100.0;

        if (length >= delta) {
            int dabs = qRound(length / delta);
            qreal angle = qAtan2(point.x() - lastPoint.x(), point.y() - lastPoint.y());
            qreal deltaX = delta * qSin(angle);
            qreal deltaY = delta * qCos(angle);

            QPointF betweenPoint;
            QRandomGenerator rg;

            for (int i = 1; i <= dabs; i++) {
                qreal x = lastPoint.x() + deltaX * i +
                        (10000 - rg.generate() % 20000) / 10000.0 * m_size * m_jitter / 100;
                qreal y = lastPoint.y() + deltaY * i +
                        (10000 - rg.generate() % 20000) / 10000.0 * m_size * m_jitter / 100;
                betweenPoint = QPointF(x, y);
                paintDab(betweenPoint, painter);

            }

            lastPoint = betweenPoint;
        }
    }
}

void BrushEngine::setLayer(Layer* layer) {
    m_layer = layer;
    m_undoImage = layer->image();
}

void BrushEngine::setCanvasBuffer(Layer* layerBuffer) {
    m_layerBuffer = layerBuffer;
}

const QByteArray& BrushEngine::undoImage() const {
    return m_undoImage;
}

const QByteArray& BrushEngine::redoImage() const {
    return m_redoImage;
}

const QColor& BrushEngine::color() const {
    return m_color;
}

void BrushEngine::setColor(const QColor& color) {
    if (m_color == color) return;
    m_color = color;
    emit colorChanged(color);
}

uint BrushEngine::size() const {
    return m_size;
}

void BrushEngine::setSize(uint size) {
    if (m_size == size) return;
    m_size = size;
    emit sizeChanged(size);
}

uint BrushEngine::hardness() const {
    return m_hardness;
}

void BrushEngine::setHardness(uint hardness) {
    if (m_hardness == hardness) return;
    m_hardness = hardness;
    emit hardnessChanged(hardness);
}

uint BrushEngine::opacity() const {
    return m_opacity;
}

void BrushEngine::setOpacity(uint opacity) {
    if (m_opacity == opacity) return;
    m_opacity = opacity;
    emit opacityChanged(opacity);
}

uint BrushEngine::flow() const {
    return m_flow;
}

void BrushEngine::setFlow(uint flow) {
    if (m_flow == flow) return;
    m_flow = flow;
    emit flowChanged(flow);
}

uint BrushEngine::roundness() const {
    return m_roundness;
}

void BrushEngine::setRoundness(uint roundness) {
    if (m_roundness == roundness) return;
    m_roundness = roundness;
    emit roundnessChanged(roundness);
}

uint BrushEngine::angle() const {
    return m_angle;
}

void BrushEngine::setAngle(uint angle) {
    if (m_angle == angle) return;
    m_angle = angle;
    emit angleChanged(angle);
}

uint BrushEngine::spacing() const {
    return m_spacing;
}

void BrushEngine::setSpacing(uint spacing) {
    if (m_spacing == spacing) return;
    m_spacing = spacing;
    emit spacingChanged(spacing);
}

uint BrushEngine::jitter() const {
    return m_jitter;
}

void BrushEngine::setJitter(uint jitter) {
    if (m_jitter == jitter) return;
    m_jitter = jitter;
    emit jitterChanged(jitter);
}

int BrushEngine::eraser() const {
    return m_eraser;
}

void BrushEngine::setEraser(uint eraser) {
    if (m_eraser == eraser) return;
    m_eraser = eraser;
    emit eraserChanged(eraser);
}

void BrushEngine::setIsTouch(bool isTouch) {
    if (m_isTouch == isTouch) return;
    m_isTouch = isTouch;

    if (isTouch) {
        startPoint = QPointF();
    } else {
        m_undoImage = m_layer->image(topleft, bottomright);

        QPainter painter(m_layer->pixmap());
        painter.setOpacity(m_opacity / 100.0);
        painter.drawPixmap(0, 0, *m_layerBuffer->pixmap());
        m_layerBuffer->pixmap()->fill(Qt::transparent);
        m_layer->update();
        m_layerBuffer->update();

        m_redoImage = m_layer->image(topleft, bottomright);

        // Correct corner positions on brush size
        topleft.setX(topleft.x() - m_size);
        topleft.setY(topleft.y() - m_size);
        bottomright.setX(bottomright.x() + m_size);
        bottomright.setY(bottomright.y() + m_size);

        topleft.setX(qMax(0, topleft.x()));
        topleft.setY(qMax(0, topleft.y()));
        bottomright.setX(qMin(m_layerBuffer->pixmap()->width(), bottomright.x()));
        bottomright.setY(qMin(m_layerBuffer->pixmap()->height(), bottomright.y()));
    }

    emit isTouchChanged(isTouch);
}

void BrushEngine::paintDab(const QPointF& point, QPainter& painter) {
    painter.save();
    painter.translate(point);
    painter.rotate(m_angle);
    painter.scale(1, m_roundness / 100.0);
    QRectF rect(-m_size / 2.0, -m_size / 2.0, m_size, m_size);
    painter.drawEllipse(rect);
    painter.restore();
    rect.moveTo(point.x() - m_size / 2.0, point.y() - m_size / 2.0);

    if (m_eraser > 50) {
        m_layer->update(rect.toRect());
    } else {
        m_layerBuffer->update(rect.toRect());
    }

    // Detect a min and max corner positions
    bottomright.setX(qMax(bottomright.x(), qRound(point.x())));
    bottomright.setY(qMax(bottomright.y(), qRound(point.y())));
    topleft.setX(qMin(topleft.x(), qRound(point.x())));
    topleft.setY(qMin(topleft.y(), qRound(point.y())));
}
