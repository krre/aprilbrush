#include "BrushEngine.h"
#include "Layer.h"
#include <QtGui>

BrushEngine::BrushEngine(QObject* parent) : QObject(parent) {

}

void BrushEngine::paint(QPixmap* pixmap, const QPointF& point, float pressure) {
    QPainter painter(pixmap);
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

    m_bound = QRect();

    if (startPoint.isNull()) {
        startPoint = point.toPoint();
        lastPoint = point.toPoint();
        topLeft = point.toPoint();
        bottomRight = point.toPoint();
        pixmapSize = pixmap->size();
        paintDab(point, painter);
        updateBound();
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
            updateBound();
        }
    }
}

void BrushEngine::finish() {
    startPoint = QPointF();
}

const QRect& BrushEngine::bound() const {
    return m_bound;
}

const QColor& BrushEngine::color() const {
    return m_color;
}

void BrushEngine::setColor(const QColor& color) {
    if (m_color == color) return;
    m_color = color;
    emit colorChanged(color);
}

int BrushEngine::size() const {
    return m_size;
}

void BrushEngine::setSize(int size) {
    if (m_size == size) return;
    m_size = size;
    emit sizeChanged(size);
}

int BrushEngine::hardness() const {
    return m_hardness;
}

void BrushEngine::setHardness(int hardness) {
    if (m_hardness == hardness) return;
    m_hardness = hardness;
    emit hardnessChanged(hardness);
}

int BrushEngine::opacity() const {
    return m_opacity;
}

void BrushEngine::setOpacity(int opacity) {
    if (m_opacity == opacity) return;
    m_opacity = opacity;

    emit opacityChanged(opacity);
}

int BrushEngine::flow() const {
    return m_flow;
}

void BrushEngine::setFlow(int flow) {
    if (m_flow == flow) return;
    m_flow = flow;
    emit flowChanged(flow);
}

int BrushEngine::roundness() const {
    return m_roundness;
}

void BrushEngine::setRoundness(int roundness) {
    if (m_roundness == roundness) return;
    m_roundness = roundness;
    emit roundnessChanged(roundness);
}

int BrushEngine::angle() const {
    return m_angle;
}

void BrushEngine::setAngle(int angle) {
    if (m_angle == angle) return;
    m_angle = angle;
    emit angleChanged(angle);
}

int BrushEngine::spacing() const {
    return m_spacing;
}

void BrushEngine::setSpacing(int spacing) {
    if (m_spacing == spacing) return;
    m_spacing = spacing;
    emit spacingChanged(spacing);
}

int BrushEngine::jitter() const {
    return m_jitter;
}

void BrushEngine::setJitter(int jitter) {
    if (m_jitter == jitter) return;
    m_jitter = jitter;
    emit jitterChanged(jitter);
}

int BrushEngine::eraser() const {
    return m_eraser;
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
    QRectF rect(-m_size / 2.0, -m_size / 2.0, m_size, m_size);
    painter.drawEllipse(rect);
    painter.restore();
    rect.moveTo(point.x() - m_size / 2.0, point.y() - m_size / 2.0);

    // Detect a min and max corner positions
    topLeft.setX(qMin(topLeft.x(), qRound(point.x())));
    topLeft.setY(qMin(topLeft.y(), qRound(point.y())));
    bottomRight.setX(qMax(bottomRight.x(), qRound(point.x())));
    bottomRight.setY(qMax(bottomRight.y(), qRound(point.y())));
}

void BrushEngine::updateBound() {
    // Correct corner positions on brush size
    topLeft.setX(topLeft.x() - m_size);
    topLeft.setY(topLeft.y() - m_size);
    bottomRight.setX(bottomRight.x() + m_size);
    bottomRight.setY(bottomRight.y() + m_size);

    // Bound to pixmap size
    topLeft.setX(qMax(0, topLeft.x()));
    topLeft.setY(qMax(0, topLeft.y()));
    bottomRight.setX(qMin(pixmapSize.width(), bottomRight.x()));
    bottomRight.setY(qMin(pixmapSize.height(), bottomRight.y()));

    m_bound = QRect(topLeft, bottomRight);
}
