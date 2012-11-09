#include "brushengine.h"
#include <qmath.h>

BrushEngine::BrushEngine()
{
    sizeBrush = 20;
    spacingBrush = 100;

    rColor = 0;
    gColor = 0;
    bColor = 0;
    aColor = 127;
}

void BrushEngine::paint(QPixmap *surfacePaint, QVector2D prevPos, QVector2D nowPos,
                        qreal prevPressure, qreal pressure)
{
    QPainter painter(surfacePaint);
    painter.setRenderHint(QPainter::Antialiasing, true);
    painter.setPen(Qt::NoPen);
    colorBrush = QColor(rColor, gColor, bColor, int(pressure * aColor));
    painter.setBrush(QBrush(colorBrush, Qt::SolidPattern));

    if (prevPos.length() == 0)
        //painter.drawEllipse(nowPos.toPoint(), sizeBrush, sizeBrush);
        painter.drawEllipse(nowPos.x(), nowPos.y(), sizeBrush, sizeBrush);
    else
    {
        qreal deltaPoint = (nowPos - prevPos).length();
        int numDabs = int(deltaPoint / sizeBrush * 100 / spacingBrush);
        qreal deltaBetweenPoint = deltaPoint / numDabs;

        qDebug() << "delta " << deltaPoint << " numDabs " << numDabs;

        if (numDabs > 0)
        {
            qreal deltaX = deltaBetweenPoint * qCos(qAtan((nowPos.y() - prevPos.y()) / (nowPos.x() - prevPos.x())));
            qreal deltaY = deltaBetweenPoint * qSin(qAtan((nowPos.y() - prevPos.y()) / (nowPos.x() - prevPos.x())));
            int xBetween = nowPos.x();
            int yBetween = nowPos.y();

            for (int countDabs = 1; countDabs <= numDabs; countDabs++)
            {
                painter.drawEllipse(xBetween, yBetween, sizeBrush, sizeBrush);
                xBetween = xBetween + int(deltaX);
                yBetween = yBetween + int(deltaY);
                qDebug() << "xBetween " << xBetween << "yBetween " << yBetween;
            }
        }
    }
}

