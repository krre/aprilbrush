#include "brushengine.h"
#include "paintspace.h"
#include <qmath.h>

BrushEngine::BrushEngine()
{
    wintabInit();
    sizeBrush = 20;
    spacingBrush = 100;
    touchPen = false;
    eraser = false;

    hardnessBrush = 80;

    rColor = 0;
    gColor = 0;
    bColor = 0;
    aColor = 127;

}

BrushEngine::~BrushEngine()
{
    //qDebug() << "bye!";
    if (ghWintab)
        FreeLibrary(ghWintab);
}

void BrushEngine::paintDab(qreal xPos, qreal yPos)
{
    qreal pressurePen = pressure();
    //qDebug() << xPos << yPos << pressurePen;
    QPointF posCursor = QPointF(xPos, yPos);
    QPainter painter(PaintSpace::pixmapPtr);
    //PaintSpace::pixmapPtr->save("D:\pix.png");
    painter.setRenderHint(QPainter::Antialiasing, true);
    painter.setPen(Qt::NoPen);
    if (eraser)
        painter.setCompositionMode(QPainter::CompositionMode_DestinationOut);

    QRadialGradient radialGradient(posCursor, sizeBrush / 2.0);
    radialGradient.setColorAt(0, QColor(rColor, gColor, bColor, qRound(pressurePen * aColor)));
    //radialGradient.setColorAt(0, QColor(rColor, gColor, bColor, qRound(pressure * alpha)));
    radialGradient.setColorAt(1, QColor(rColor, gColor, bColor, 0));
    radialGradient.setColorAt(hardnessBrush / 100.0, QColor(rColor, gColor, bColor, qRound(pressurePen * aColor)));
    //radialGradient.setColorAt(hardnessBrush / 100.0, QColor(rColor, gColor, bColor, qRound(pressure * alpha)));
    painter.setBrush(QBrush(radialGradient));

    qreal length;
    int numDabs;
    qreal deltaDab;
    qreal angle;
    QPointF betweenPos;

    //painter.drawEllipse(posCursor, sizeBrush / 2.0, sizeBrush / 2.0);

    // First dab after touching the stylus at a surface
    if (!touchPen)
    {
        prevPos = posCursor;
        painter.drawEllipse(posCursor, sizeBrush / 2.0, sizeBrush / 2.0);
        touchPen = true;
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
                radialGradient.setColorAt(0, QColor(rColor, gColor, bColor, qRound(pressurePen * aColor)));
                //radialGradient.setColorAt(0, QColor(rColor, gColor, bColor, qRound(pressure * alpha)));
                radialGradient.setColorAt(1, QColor(rColor, gColor, bColor, 0));
                radialGradient.setColorAt(hardnessBrush / 100.0, QColor(rColor, gColor, bColor, qRound(pressurePen * aColor)));
                //radialGradient.setColorAt(hardnessBrush / 100.0, QColor(rColor, gColor, bColor, qRound(pressure * alpha)));

                painter.setBrush(QBrush(radialGradient));
                painter.drawEllipse(betweenPos, sizeBrush / 2.0, sizeBrush / 2.0);
                prevPos = betweenPos;
            }
        }
    }
}

void BrushEngine::clear()
{
    PaintSpace::pixmapPtr->fill(QColor("white"));
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
