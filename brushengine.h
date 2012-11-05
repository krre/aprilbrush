#ifndef BRUSHENGINE_H
#define BRUSHENGINE_H

#include <QtGui>

class BrushEngine : public QObject
{
    Q_OBJECT

public:
    BrushEngine();
    void paint(QPixmap *surfacePaint, int inputPosX, int inputPosY, qreal inputPressure);
    inline void setColor(int r, int g, int b) {rColor = r; gColor = g, bColor = b;}


public slots:
    inline void setSizeBrush(int size) {sizeBrush = size;}

private:
    QColor colorBrush;
    int sizeBrush;
    int rColor;
    int gColor;
    int bColor;
};

#endif // BRUSHENGINE_H
