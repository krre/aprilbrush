#include "brushengine.h"

void BrushEngine::paint(float x, float y, CanvasItem* canvasItem, float pressure)
{
    qDebug() << x << y << pressure << *canvasItem->image();
}
