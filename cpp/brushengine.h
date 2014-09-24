#ifndef BRUSHENGINE_H
#define BRUSHENGINE_H

#include <QtCore>
#include "canvasitem.h"

class BrushEngine : public QObject
{
    Q_OBJECT
public:
    explicit BrushEngine(QObject *parent = 0);
    Q_INVOKABLE void paint(QPointF point, CanvasItem *canvas);

signals:

public slots:

};

#endif // BRUSHENGINE_H
