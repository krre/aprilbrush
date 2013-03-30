#include "brushengine.h"
#include <qmath.h>
#include <QDebug>

BrushEngine::BrushEngine()
{
    wintabInit();
    //ghWintab = 0;
    touchPen = false;
    eraserBrush = false;
    //qDebug() << "brush engine starts";
}

BrushEngine::~BrushEngine()
{
    //qDebug() << "bye!";
    if (ghWintab)
        FreeLibrary(ghWintab);
}

void BrushEngine::paintDab(qreal xPos, qreal yPos)
{
    QPointF posCursor = QPointF(xPos, yPos);
    // First dab after touching the stylus at a surface
    if (!touchPen)
    {
        prevPos = posCursor;
        //prevPixmap = new QPixmap(paintedItem->pixmapItem);
        minPos = QPoint(prevPos.x(), prevPos.y());
        maxPos = minPos;
        touchPen = true;
    }

    colorBrush.setAlpha(qRound(255 * opacityBrush / 100.0));
    QColor pressureColor = colorBrush;
    qreal pressurePen = pressure();
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
        //undoByteArray = compressPixmap(prevPixmap->copy(QRect(minPos, maxPos)));
        // Redo area compress
        //redoByteArray = compressPixmap(paintedItem->pixmapItem.copy(QRect(minPos, maxPos)));

        //delete prevPixmap;
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

void BrushEngine::wintabInit()
{
    ghWintab = LoadLibraryA("Wintab32.dll");
    //qDebug() << "LoadLibrary: " << ghWintab;
    if (!ghWintab)
        return;

    ptrWTInfo = (PtrWTInfo)GetProcAddress(ghWintab, "WTInfoW");
    ptrWTOpen = (PtrWTOpen)GetProcAddress(ghWintab, "WTOpenW");
    ptrWTPacket = (PtrWTPacket)GetProcAddress(ghWintab, "WTPacket");
    ptrWTQueuePacketsEx = (PtrWTQueuePacketsEx)GetProcAddress(ghWintab, "WTQueuePacketsEx");

    // Check device name
    char deviceName[50] = {0};
    ptrWTInfo(WTI_DEVICES, DVC_NAME, deviceName);
    //qDebug() << (const char*)&deviceName;

    // Default context
    LOGCONTEXT tabletContext;
    ptrWTInfo(WTI_DEFCONTEXT, 0, &tabletContext);
    //qDebug() << "Context: " << wacomContext.lcName;

    // Modify the region
    tabletContext.lcPktData = PACKETDATA;
    tabletContext.lcPktMode = PACKETMODE;
    tabletContext.lcMoveMask = PACKETDATA;
    tabletContext.lcOptions |= CXO_SYSTEM; // enable tablet cursor move

    HWND windowHandle = GetDesktopWindow();
    //qDebug() << "Window handle: " << windowHandle;

    tabletHandle = ptrWTOpen(windowHandle, &tabletContext, true);
    //qDebug() << "Tablet handle: " << tabletHandle;
}

qreal BrushEngine::pressure()
{
    qreal pressure = 1;
    if (ghWintab)
    {
        PACKET packet;
        UINT FAR lpOld;
        UINT FAR lpNew;
        bool serialPacket = ptrWTQueuePacketsEx(tabletHandle, &lpOld, &lpNew);
        ptrWTPacket(tabletHandle, lpNew, &packet);
        if (serialPacket)
            pressure = (qreal)packet.pkNormalPressure / 1023;
    }
    return pressure;
}
