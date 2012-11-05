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
    inline void setColor(int r, int g, int b, int a) {rColor = r; gColor = g, bColor = b; aColor = a;}


public slots:
    inline void setSizeBrush(int size) {sizeBrush = size;}
    inline void setAlpha(int alpha) {aColor = int(alpha * 255 / 100);}

private:
    QColor colorBrush;
    int sizeBrush;
    int rColor;
    int gColor;
    int bColor;
    int aColor;
};

#endif // BRUSHENGINE_H
