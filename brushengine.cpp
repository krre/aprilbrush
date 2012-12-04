#include "brushengine.h"
#include <qmath.h>

BrushEngine::BrushEngine()
{
    sizeBrush = 20;
    spacingBrush = 100;
    touchStylus = false;

    rColor = 0;
    gColor = 0;
    bColor = 0;
    aColor = 127;
}

void BrushEngine::paint(QPixmap *pixmap, QPoint posCursor, qreal pressure)
{
    QPainter painter(pixmap);
    painter.setRenderHint(QPainter::Antialiasing, true);
    painter.setPen(Qt::NoPen);
    colorBrush = QColor(rColor, gColor, bColor, int(pressure * aColor));
    painter.setBrush(QBrush(colorBrush, Qt::SolidPattern));
    qreal length;
    int numDabs;
    qreal deltaDab;
    qreal angle;
    QPoint betweenPos;

    // First dab after touching the stylus at a surface
    if (!touchStylus)
    {
        prevPos = posCursor;
        painter.drawEllipse(posCursor.x() - sizeBrush / 2, posCursor.y() - sizeBrush / 2, sizeBrush, sizeBrush);
        touchStylus = true;
    }
    else
    {
        nowPos = posCursor;
        length = qSqrt(qPow(prevPos.x() - nowPos.x(), 2) + qPow(prevPos.y() - nowPos.y(), 2));
        deltaDab = sizeBrush * spacingBrush / 100.0;
        if (length >= deltaDab)
        {
            numDabs = qRound(length / deltaDab);
            angle = qAtan2(nowPos.x() - prevPos.x(), nowPos.y() - prevPos.y());
            for (int dabCount = 1; dabCount <= numDabs; dabCount++)
            {
                betweenPos = QPoint(prevPos.x() + deltaDab * qSin(angle), prevPos.y() + deltaDab * qCos(angle));
                painter.drawEllipse(betweenPos.x() - sizeBrush / 2, betweenPos.y() - sizeBrush / 2, sizeBrush, sizeBrush);
                prevPos = betweenPos;
            }            
        }
    }
}

