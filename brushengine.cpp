#include "brushengine.h"

BrushEngine::BrushEngine()
{
    sizeBrush = 15;
    //colorBrush = QColor(0, 255, 0, 255);
    rColor = 0;
    gColor = 255;
    bColor = 0;
    aColor = 255;
}

void BrushEngine::paint(QPixmap *surfacePaint, int inputPosX, int inputPosY, qreal inputPressure)
{
    QPainter painter(surfacePaint);
    painter.setRenderHint(QPainter::Antialiasing, true);
    painter.setPen(Qt::NoPen);
    colorBrush = QColor(rColor, gColor, bColor, int(inputPressure * aColor));
    painter.setBrush(QBrush(colorBrush, Qt::SolidPattern));
    painter.drawEllipse(inputPosX, inputPosY, sizeBrush, sizeBrush);
}

