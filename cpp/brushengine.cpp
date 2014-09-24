#include "brushengine.h"

BrushEngine::BrushEngine(QObject *parent) :
    QObject(parent)
{
}

void BrushEngine::paint(QPointF point, CanvasItem *canvas)
{
    QPixmap *pixmap = canvas->pixmap();

    m_color.setAlpha(qRound(255 * m_opacity / 100.0));
//    QColor pressureColor = m_color;
//    qreal pressure = wacom.pressure();
//    pressureColor.setAlpha(qRound(m_color.alpha() * pressure));
//    QColor alphaColor =  m_color;
//    alphaColor.setAlpha(0);

    QPainter painter(pixmap);
    painter.setRenderHint(QPainter::Antialiasing, true);
    painter.setPen(Qt::NoPen);
    painter.setBrush(QBrush(m_color));
    if (m_size > 1) {
        painter.drawEllipse(point, m_size / 2, m_size / 2);
    } else {
        painter.drawRect(QRectF(point.x() - 0.5, point.y() - 0.5, 1, 1));
    }
    painted();
}
