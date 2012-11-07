#ifndef CANVAS_H
#define CANVAS_H

#include <QtGui>
#include "brushengine.h"

class Canvas : public QWidget
{
    Q_OBJECT

public:
    Canvas(BrushEngine *globalBrush);

    //inline int getXPos() {return xPos;}
    //inline int getYPos() {return yPos;}
    inline QVector2D getVectorPoint() {return nowPos;}
    inline qreal getPressure() {return pressure;}
    inline QString getTypeDevice() {return typeDevice;}

protected:
    void paintEvent(QPaintEvent*);
    void mouseMoveEvent(QMouseEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void tabletEvent(QTabletEvent *event);

signals:
    void inputEvent();
    
public slots:
    void clearCanvas();

private:
    BrushEngine *brush;
    QPixmap pixmap;
    QVector2D nowPos;
    QVector2D prevPos;
    //int xPos;
    //int xPrevPos;
    //int yPos;
    //int yPrevPos;
    qreal pressure;
    qreal pressurePrev;
    QString typeDevice;
};

#endif // CANVAS_H
