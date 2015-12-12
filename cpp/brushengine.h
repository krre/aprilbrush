#pragma once
#include <QtCore>
#include "canvasitem.h"

class BrushEngine : public QObject
{
    Q_OBJECT
public:
    BrushEngine() {}
    Q_INVOKABLE void paint(float x, float y, CanvasItem* canvasItem, float pressure=1.0);
};
