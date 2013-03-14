#include "brushengine.h"
#include "paintspace.h"
#include <qmath.h>

QPixmap *BrushEngine::pixmap;
QQuickPaintedItem *BrushEngine::paintedLayer;

BrushEngine::BrushEngine()
{
    wintabInit();
    //ghWintab = 0;
    touchPen = false;
    eraser = false;
}

BrushEngine::~BrushEngine()
{
    //qDebug() << "bye!";
    if (ghWintab)
        FreeLibrary(ghWintab);
}

void BrushEngine::setLayer(long hashPageLayer)
{
    pixmap = PaintSpace::pixmapHash[hashPageLayer];
    paintedLayer = PaintSpace::paintItemHash[hashPageLayer];
    qDebug() << pixmap << hashPageLayer;
    qDebug() << PaintSpace::pixmapHash;
}

void BrushEngine::paintDab(qreal xPos, qreal yPos)
{
    colorBrush.setAlpha(qRound(255 * opacityBrush / 100.0));
    QColor pressureColor = colorBrush;
    qreal pressurePen = pressure();
    pressureColor.setAlpha(qRound(colorBrush.alpha() * pressurePen));
    QColor alphaColor =  colorBrush;
    alphaColor.setAlpha(0);
    //qDebug() << xPos << yPos << pressurePen;
    QPointF posCursor = QPointF(xPos, yPos);

    QPainter painter(pixmap);
    painter.setRenderHint(QPainter::Antialiasing, true);
    painter.setPen(Qt::NoPen);

    QRadialGradient radialGradient;
    radialGradient.setRadius(sizeBrush / 2.0);
    radialGradient.setColorAt(0, pressureColor);
    radialGradient.setColorAt(hardnessBrush / 100.0, pressureColor);
    radialGradient.setColorAt(1, alphaColor);
    painter.setBrush(QBrush(radialGradient));

    if (eraser)
        painter.setCompositionMode(QPainter::CompositionMode_DestinationOut);

    // First dab after touching the stylus at a surface
    if (!touchPen)
    {
        prevPos = posCursor;
        touchPen = true;
    }
    else
    {
        qreal length;
        int numDabs;
        qreal deltaDab;
        qreal angle;
        QPointF betweenPos;

        nowPos = posCursor;
        length = qSqrt(qPow(prevPos.x() - nowPos.x(), 2) + qPow(prevPos.y() - nowPos.y(), 2));
        deltaDab = sizeBrush * spacingBrush / 100.0;
        qreal sizeBrushHalf = sizeBrush / 2.0; // for increasing of the painting speed
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
                painter.restore();
                prevPos = betweenPos;
                paintedLayer->update();
                emit paintDone();
            }
        }
    }
}

void BrushEngine::setTouch(bool touch)
{
    touchPen = touch;
}

void BrushEngine::clear()
{
    pixmap->fill(QColor(0, 0, 0, 0));
    paintedLayer->update();
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
