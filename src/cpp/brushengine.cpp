#include "brushengine.h"

void BrushEngine::paint(const QPointF& point, CanvasItem* canvasItem, float pressure)
{
//    qDebug() << x << y << pressure;
    QPainter painter(canvasItem->pixmap());
    painter.setRenderHint(QPainter::Antialiasing, true);
    painter.setPen(Qt::NoPen);

    m_color.setAlpha(qRound(255 * m_opacity / 100.0));
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

//    QPointF betweenPoint = QPointF(x, y);
    painter.save();
    painter.translate(point);
//    painter.rotate(m_angle);
    painter.scale(1, m_roundness / 100.0);
    painter.drawEllipse(-m_size / 2.0, -m_size / 2.0, m_size, m_size);
    painter.restore();
    canvasItem->update();
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
