#include "brushengine.h"

void BrushEngine::paint(float x, float y, CanvasItem* canvasItem, float pressure)
{
//    qDebug() << x << y << pressure;
    QPainter painter(canvasItem->pixmap());
    painter.setRenderHint(QPainter::Antialiasing, true);
    painter.setPen(Qt::NoPen);

    int m_hardness = 80;

    QColor pressureColor = m_color;
    QColor alphaColor = m_color;

    QRadialGradient radialGradient;
    radialGradient.setRadius(m_size / 2.0);
    radialGradient.setColorAt(0, pressureColor);
    radialGradient.setColorAt(1, alphaColor);
    radialGradient.setColorAt(m_hardness / 100.0, pressureColor);
    painter.setBrush(QBrush(radialGradient));

    QPointF betweenPoint = QPointF(x, y);
    painter.save();
    painter.translate(betweenPoint);
//    painter.rotate(m_angle);
//    painter.scale(1, 1.0 / m_roundness);
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
