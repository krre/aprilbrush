#include "brushengine.h"

void BrushEngine::paint(float x, float y, CanvasItem* canvasItem)
{
    qDebug() << x << y << *canvasItem->image();
}

