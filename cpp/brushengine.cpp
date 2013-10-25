/* AprilBrush - Digital Painting Software
 * Copyright (C) 2012-2013 Vladimir Zarypov <krre@mail.ru>
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation;
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 */

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
    qreal tunedOpacity = m_opacity * (m_spacing > 100 ? 100 : m_spacing) / 100.0;
    m_color.setAlpha(qRound(255 * tunedOpacity / 100.0));
    QColor pressureColor = m_color;
    qreal pressure = 1.0; // temporary setted to 1
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
        qreal deltaX = deltaDab * qSin(angle);
        qreal deltaY = deltaDab * qCos(angle);
        QPointF betweenPoint;
        for (int i = 1; i <= numDabs; i++)
        {
            qreal x = prevPoint.x() + deltaX * i +
                    (10000 - qrand() % 20000) / 10000.0 * m_size * m_jitter / 100;
            qreal y = prevPoint.y() + deltaY * i +
                    (10000 - qrand() % 20000) / 10000.0 * m_size * m_jitter / 100;
            betweenPoint = QPointF(x, y);
            painter.save();
            painter.translate(betweenPoint);
            painter.rotate(m_angle);
            painter.scale(1, 1.0 / m_roundness);
            painter.drawEllipse(-m_size / 2.0, -m_size / 2.0, m_size, m_size);
            painter.restore();

            // Detect a min and max corner positions
            maxPoint.setX(qMax(maxPoint.x(), qRound(betweenPoint.x())));
            maxPoint.setY(qMax(maxPoint.y(), qRound(betweenPoint.y())));
            minPoint.setX(qMin(minPoint.x(), qRound(betweenPoint.x())));
            minPoint.setY(qMin(minPoint.y(), qRound(betweenPoint.y())));
            emit paintDone();
        }
        prevPoint = betweenPoint;
    }
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

    if (minPoint.x() < 0) minPoint.setX(0);
    if (minPoint.y() < 0) minPoint.setY(0);
    if (maxPoint.x() > pixmap->width()) maxPoint.setX(pixmap->width());
    if (maxPoint.y() > pixmap->height()) maxPoint.setY(pixmap->height());

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
    }
}

QByteArray BrushEngine::compressPixmap(QPixmap pixmap)
{
    QByteArray byteArray;
    QBuffer buffer(&byteArray);
    buffer.open(QIODevice::WriteOnly);
    pixmap.save(&buffer, "TIF");
    buffer.close();
    return byteArray;
}

