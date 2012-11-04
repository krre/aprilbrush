#ifndef BRUSHENGINE_H
#define BRUSHENGINE_H

#include <QtGui>

class BrushEngine : public QObject
{
    Q_OBJECT

public:
    BrushEngine();
    void paint(QPixmap *surfacePaint, int inputPosX, int inputPosY, qreal inputPressure);

public slots:
    inline void setSizeBrush(int size) {sizeBrush = size;}

private:
    QColor colorBrush;
    int sizeBrush;
};

#endif // BRUSHENGINE_H
