#include "brushengine.h"
#include <qmath.h>

BrushEngine::BrushEngine()
{
    sizeBrush = 20;
    spacingBrush = 100;
    touchStylus = false;
    eraser = false;

    hardnessBrush = 80;

    rColor = 0;
    gColor = 0;
    bColor = 0;
    aColor = 127;
}

void BrushEngine::paintDab(QPixmap *pixmap, QPointF posCursor, qreal pressure)
{
    QPainter painter(pixmap);
    painter.setRenderHint(QPainter::Antialiasing, true);
    painter.setPen(Qt::NoPen);
    if (eraser)
        painter.setCompositionMode(QPainter::CompositionMode_DestinationOut);

    //qreal alpha = aColor;
    //if (spacingBrush < 100)
    //    alpha = aColor * spacingBrush / 100.0;

    QRadialGradient radialGradient(posCursor, sizeBrush / 2.0);
    radialGradient.setColorAt(0, QColor(rColor, gColor, bColor, qRound(pressure * aColor)));
    //radialGradient.setColorAt(0, QColor(rColor, gColor, bColor, qRound(pressure * alpha)));
    radialGradient.setColorAt(1, QColor(rColor, gColor, bColor, 0));
    radialGradient.setColorAt(hardnessBrush / 100.0, QColor(rColor, gColor, bColor, qRound(pressure * aColor)));
    //radialGradient.setColorAt(hardnessBrush / 100.0, QColor(rColor, gColor, bColor, qRound(pressure * alpha)));
    painter.setBrush(QBrush(radialGradient));

    qreal length;
    int numDabs;
    qreal deltaDab;
    qreal angle;
    QPointF betweenPos;

    // First dab after touching the stylus at a surface
    if (!touchStylus)
    {
        prevPos = posCursor;
        painter.drawEllipse(posCursor, sizeBrush / 2.0, sizeBrush / 2.0);
        touchStylus = true;
    }
    else
    {
        nowPos = posCursor;
        length = qSqrt(qPow(prevPos.x() - nowPos.x(), 2) + qPow(prevPos.y() - nowPos.y(), 2));
        deltaDab = sizeBrush * spacingBrush / 100.0;
        // Drawing dabs between the events
        if (length >= deltaDab)
        {
            numDabs = qRound(length / deltaDab);
            angle = qAtan2(nowPos.x() - prevPos.x(), nowPos.y() - prevPos.y());
            for (int dabCount = 1; dabCount <= numDabs; dabCount++)
            {
                betweenPos = QPointF(prevPos.x() + deltaDab * qSin(angle), prevPos.y() + deltaDab * qCos(angle));
                //radialGradient.setCenter(betweenPos);

                // temporary
                radialGradient = QRadialGradient(betweenPos, sizeBrush / 2.0);
                radialGradient.setColorAt(0, QColor(rColor, gColor, bColor, qRound(pressure * aColor)));
                //radialGradient.setColorAt(0, QColor(rColor, gColor, bColor, qRound(pressure * alpha)));
                radialGradient.setColorAt(1, QColor(rColor, gColor, bColor, 0));
                radialGradient.setColorAt(hardnessBrush / 100.0, QColor(rColor, gColor, bColor, qRound(pressure * aColor)));
                //radialGradient.setColorAt(hardnessBrush / 100.0, QColor(rColor, gColor, bColor, qRound(pressure * alpha)));

                painter.setBrush(QBrush(radialGradient));
                painter.drawEllipse(betweenPos, sizeBrush / 2.0, sizeBrush / 2.0);
                prevPos = betweenPos;
            }            
        }
    }
}

