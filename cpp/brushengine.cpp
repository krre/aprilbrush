#include "brushengine.h"
#include <qmath.h>

#include <QBuffer>
#include <QDebug>

BrushEngine::BrushEngine()
{
    m_eraser = false;
}

void BrushEngine::paintDab(QPoint nowPoint)
{
    m_color.setAlpha(qRound(255 * m_opacity / 100.0));
    QColor pressureColor = m_color;
    qreal pressure = wacom.pressure();
    pressureColor.setAlpha(qRound(m_color.alpha() * pressure));
    QColor alphaColor =  m_color;
    alphaColor.setAlpha(0);

    QPainter painter(pixmap);
    painter.setRenderHint(QPainter::Antialiasing, true);
    painter.setPen(Qt::NoPen);

    QRadialGradient radialGradient;
    radialGradient.setRadius(m_size / 2.0);
    radialGradient.setColorAt(0, pressureColor);
    radialGradient.setColorAt(1, alphaColor);
    radialGradient.setColorAt(m_hardness / 100.0, pressureColor);
    painter.setBrush(QBrush(radialGradient));

    if (m_eraser)
        painter.setCompositionMode(QPainter::CompositionMode_DestinationOut);

    qreal length = qSqrt(qPow(prevPoint.x() - nowPoint.x(), 2) + qPow(prevPoint.y() - nowPoint.y(), 2));
    qreal deltaDab = m_size * m_spacing / 100.0;
    // Drawing dabs between the events
    if (length >= deltaDab)
    {
        int numDabs = qRound(length / deltaDab);
        qreal angle = qAtan2(nowPoint.x() - prevPoint.x(), nowPoint.y() - prevPoint.y());
        QPointF betweenPoint;
        for (int dabCount = 1; dabCount <= numDabs; dabCount++)
        {
            betweenPoint = QPointF(prevPoint.x() + deltaDab * qSin(angle), prevPoint.y() + deltaDab * qCos(angle));
            painter.save();
            painter.translate(betweenPoint);
            painter.rotate(m_angle);
            painter.scale(1, 1.0 / m_roundness);
            painter.drawEllipse(-m_size / 2.0, -m_size / 2.0, m_size, m_size);
            painter.restore();

            prevPoint = betweenPoint.toPoint();
        }
    }

    // Detect a min and max corner positions
    maxPoint.setX(qMax(maxPoint.x(), nowPoint.x()));
    maxPoint.setY(qMax(maxPoint.y(), nowPoint.y()));
    minPoint.setX(qMin(minPoint.x(), nowPoint.x()));
    minPoint.setY(qMin(minPoint.y(), nowPoint.y()));
}

void BrushEngine::setTouch(QPoint nowPoint)
{
    prevPoint = nowPoint;
    prevPixmap = new QPixmap(*pixmap);
    minPoint = QPoint(pixmap->width(), pixmap->height());
    maxPoint = QPoint(0, 0);
}

void BrushEngine::setUnTouch()
{
    // Correct corner positions on brush size
    minPoint.setX(minPoint.x() - m_size);
    minPoint.setY(minPoint.y() - m_size);
    maxPoint.setX(maxPoint.x() + m_size);
    maxPoint.setY(maxPoint.y() + m_size);

    // Undo area compress
    undoByteArray = compressPixmap(prevPixmap->copy(QRect(minPoint, maxPoint)));
    // Redo area compress
    redoByteArray = compressPixmap(pixmap->copy(QRect(minPoint, maxPoint)));

    delete prevPixmap;
}

void BrushEngine::setLayerId(QString arg)
{
    if (arg != "") {
        m_layerId = arg;
        pixmap = m_imageProcessor->pixmapHash()[m_layerId];
        //qDebug() << "m_layerId" << m_layerId << m_imageProcessor->pixmapHash() << *pixmap;
    }
}

QByteArray BrushEngine::compressPixmap(QPixmap pixmap)
{
    QByteArray byteArray;
    QBuffer buffer(&byteArray);
    buffer.open(QIODevice::WriteOnly);
    pixmap.save(&buffer, "TIF");
    buffer.close();
    byteArray = qCompress(byteArray);
    return byteArray;
}

