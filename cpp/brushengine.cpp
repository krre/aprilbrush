#include "brushengine.h"
#include <qmath.h>
#include <QDebug>

BrushEngine::BrushEngine()
{
    touchPen = false;
    eraserBrush = false;
}

void BrushEngine::paintDab(qreal xPos, qreal yPos)
{
    QPointF posCursor = QPointF(xPos, yPos);
    // First dab after touching the stylus at a surface
    if (!touchPen)
    {
        prevPos = posCursor;
        prevPixmap = new QPixmap(*pixmap);
        minPos = QPoint(prevPos.x(), prevPos.y());
        maxPos = minPos;
        touchPen = true;
    }

    colorBrush.setAlpha(qRound(255 * opacityBrush / 100.0));
    QColor pressureColor = colorBrush;
    qreal pressurePen = wacom.pressure();
    pressureColor.setAlpha(qRound(colorBrush.alpha() * pressurePen));
    QColor alphaColor =  colorBrush;
    alphaColor.setAlpha(0);

    QPainter painter(pixmap);
    //qDebug() << "pixmap" << pixmap;
    painter.setRenderHint(QPainter::Antialiasing, true);
    painter.setPen(Qt::NoPen);

    QRadialGradient radialGradient;
    radialGradient.setRadius(sizeBrush / 2.0);
    radialGradient.setColorAt(0, pressureColor);
    radialGradient.setColorAt(hardnessBrush / 100.0, pressureColor);
    radialGradient.setColorAt(1, alphaColor);
    painter.setBrush(QBrush(radialGradient));
    //qDebug() << pressureColor << hardnessBrush << alphaColor << painter.brush();

    if (eraserBrush)
        painter.setCompositionMode(QPainter::CompositionMode_DestinationOut);

    qreal length;
    int numDabs;
    qreal deltaDab;
    qreal angle;
    QPointF betweenPos;

    nowPos = posCursor;
    length = qSqrt(qPow(prevPos.x() - nowPos.x(), 2) + qPow(prevPos.y() - nowPos.y(), 2));
    deltaDab = sizeBrush * spacingBrush / 100.0;
    qreal sizeBrushHalf = sizeBrush / 2.0; // for increasing painting speed
    // Drawing dabs between the events
    if (length >= deltaDab)
    {
        numDabs = qRound(length / deltaDab);
        angle = qAtan2(nowPos.x() - prevPos.x(), nowPos.y() - prevPos.y());
        for (int dabCount = 1; dabCount <= numDabs; dabCount++)
        {
            betweenPos = QPointF(prevPos.x() + deltaDab * qSin(angle), prevPos.y() + deltaDab * qCos(angle));
            painter.save();
            painter.translate(betweenPos);
            painter.rotate(angleBrush);
            painter.scale(1, 1.0 / roundnessBrush);
            painter.drawEllipse(-sizeBrushHalf, -sizeBrushHalf, sizeBrush, sizeBrush);
            emit paintDone(QRect(qRound(betweenPos.x() - sizeBrush / 2), qRound(betweenPos.y() - sizeBrush / 2), sizeBrush, sizeBrush));
            painter.restore();

            // Detect a min and max corner positions
            if (betweenPos.x() > maxPos.x()) maxPos.setX(betweenPos.x());
            if (betweenPos.x() < minPos.x()) minPos.setX(betweenPos.x());
            if (betweenPos.y() > maxPos.y()) maxPos.setY(betweenPos.y());
            if (betweenPos.y() < minPos.y()) minPos.setY(betweenPos.y());
            //qDebug() << betweenPos;

            prevPos = betweenPos;
        }
    }
}

void BrushEngine::setTouch(bool touch)
{
    touchPen = touch;
    if (!touchPen) {

        // Correct corner positions on brush size
        minPos.setX(minPos.x() - sizeBrush / 2);
        minPos.setY(minPos.y() - sizeBrush / 2);
        maxPos.setX(maxPos.x() + sizeBrush / 2);
        maxPos.setY(maxPos.y() + sizeBrush / 2);

        // Undo area compress
        undoByteArray = compressPixmap(prevPixmap->copy(QRect(minPos, maxPos)));
        // Redo area compress
        redoByteArray = compressPixmap(pixmap->copy(QRect(minPos, maxPos)));

        delete prevPixmap;
    }
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

