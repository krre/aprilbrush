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

void BrushEngine::paint(QPixmap *pixmap, QPoint posCursor, qreal pressure)
{
    //QTime nowTime;
    //nowTime.currentTime();
    //nowTime = QTime::currentTime();
    //int diffTime = nowMS - time.msec();
    //qDebug() << "now time: " << nowMS << "prev time: " << time.msec() << "diff time: " << diffTime;
    //float diffTime = nowTime - time;
    //time = nowTime;
    //qDebug() << diffTime;

    QPainter painter(pixmap);
    painter.setRenderHint(QPainter::Antialiasing, true);
    painter.setPen(Qt::NoPen);
    colorBrush = QColor(rColor, gColor, bColor, int(pressure * aColor));
    painter.setBrush(QBrush(colorBrush, Qt::SolidPattern));
    painter.drawEllipse(posCursor.x(), posCursor.y(), sizeBrush, sizeBrush);

    /*

    if (prevPos.length() == 0)
        //painter.drawEllipse(posCursor.toPoint(), sizeBrush, sizeBrush);
        painter.drawEllipse(posCursor.x(), posCursor.y(), sizeBrush, sizeBrush);
    else
    {
        qreal deltaPoint = (posCursor - prevPos).length();
        int numDabs = int(deltaPoint / sizeBrush * 100 / spacingBrush);
        qreal deltaBetweenPoint = deltaPoint / numDabs;

        qDebug() << "delta " << deltaPoint << " numDabs " << numDabs;

        if (numDabs > 0)
        {
            qreal deltaX = deltaBetweenPoint * qCos(qAtan((posCursor.y() - prevPos.y()) / (posCursor.x() - prevPos.x())));
            qreal deltaY = deltaBetweenPoint * qSin(qAtan((posCursor.y() - prevPos.y()) / (posCursor.x() - prevPos.x())));
            int xBetween = posCursor.x();
            int yBetween = posCursor.y();

            for (int countDabs = 1; countDabs <= numDabs; countDabs++)
            {
                painter.drawEllipse(xBetween, yBetween, sizeBrush, sizeBrush);
                xBetween = xBetween + int(deltaX);
                yBetween = yBetween + int(deltaY);
                qDebug() << "xBetween " << xBetween << "yBetween " << yBetween;
            }
        }
    }
    */
}

