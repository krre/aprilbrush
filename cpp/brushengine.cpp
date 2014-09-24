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
    painter.drawEllipse(point, m_size / 2, m_size / 2);
}
