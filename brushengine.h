#ifndef BRUSHENGINE_H
#define BRUSHENGINE_H

#include <QtGui>

class BrushEngine
{
public:
    BrushEngine();
    void paint(QPixmap *surfacePaint, int inputPosX, int inputPosY, int inputPressure);

    QColor colorBrush;
    int sizeBrush;

private:
};

#endif // BRUSHENGINE_H
