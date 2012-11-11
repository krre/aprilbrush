#ifndef CANVAS_H
#define CANVAS_H

#include <QtGui>
#include "brushengine.h"

class Canvas : public QWidget
{
    Q_OBJECT

public:
    Canvas(BrushEngine *globalBrush);
    inline QPoint getPosCursor() {return posCursor;}
    inline qreal getPressure() {return pressure;}
    inline QString getTypeDevice() {return typeDevice;}

protected:
    void paintEvent(QPaintEvent*);
    void mouseMoveEvent(QMouseEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void tabletEvent(QTabletEvent *event);

signals:
    void inputEventSignal();
    
public slots:
    void clearCanvasSlot();

private:
    BrushEngine *brush;
    QPixmap *pixmap;
    QPoint posCursor;
    qreal pressure;
    QString typeDevice;
};

#endif // CANVAS_H
