#ifndef BRUSHENGINE_H
#define BRUSHENGINE_H

#include <QtGui>

class BrushEngine : public QObject
{
    Q_OBJECT

public:
    BrushEngine();
    void paint(QPixmap *pixmap, QPoint posCursor, qreal pressure);
    inline int diameterBrush() {return sizeBrush;}
    inline void setColor(int r, int g, int b) {rColor = r; gColor = g, bColor = b;}
    inline void setColor(int r, int g, int b, int a) {rColor = r; gColor = g, bColor = b; aColor = a;}
    inline bool touch() {return touchStylus;}
    inline void setTouch(bool touch) {touchStylus = touch;}

signals:
    void sizeBrushSignal();

public slots:
    inline void setSizeBrush(int size) {sizeBrush = size; emit sizeBrushSignal();}
    inline void setAlpha(int alpha) {aColor = int(alpha * 255 / 100);}
    inline void setSpacingBrush(int spacing) {spacingBrush = spacing;}
    inline void setHardnessBrush(int hardness) {hardnessBrush = hardness;}

private:
    QColor colorBrush;
    int sizeBrush;
    int spacingBrush;
    int hardnessBrush;

    QPointF nowPos;
    QPointF prevPos;
    bool touchStylus;

    int rColor;
    int gColor;
    int bColor;
    int aColor;

    QTime time;
};

#endif // BRUSHENGINE_H
