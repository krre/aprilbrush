#include "brushengine.h"

BrushEngine::BrushEngine()
{
    sizeBrush = 15;
    colorBrush = QColor(0, 255, 0, 255);
}

void BrushEngine::paint(QPixmap *surfacePaint, int inputPosX, int inputPosY, qreal inputPressure)
{
    QPainter painter(surfacePaint);
    painter.setRenderHint(QPainter::Antialiasing, true);
    painter.setPen(Qt::NoPen);
    colorBrush = QColor(0, 255, 0, int(inputPressure * 255));
    painter.setBrush(QBrush(colorBrush, Qt::SolidPattern));
    painter.drawEllipse(inputPosX, inputPosY, sizeBrush, sizeBrush);
}

