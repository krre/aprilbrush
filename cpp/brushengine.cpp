#include "brushengine.h"

BrushEngine::BrushEngine(QObject *parent) :
    QObject(parent)
{
}

void BrushEngine::paint(QPointF point, CanvasItem *canvas)
{
    QPixmap *pixmap = canvas->pixmap();
}
