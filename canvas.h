#ifndef CANVAS_H
#define CANVAS_H

#include <QtGui>
#include "brushengine.h"

class Canvas : public QWidget
{
    Q_OBJECT

public:
    Canvas(BrushEngine *globalBrush);

    inline int getXPos() {return xPos;}
    inline int getYPos() {return yPos;}
    inline qreal getPressure() {return pressure;}
    inline QString getTypeDevice() {return typeDevice;}

protected:
    void paintEvent(QPaintEvent*);
    void mouseMoveEvent(QMouseEvent *event);
    void tabletEvent(QTabletEvent *event);

signals:
    void inputEvent();
    
public slots:
    void clearAction();

private:
    BrushEngine *brush;
    QPixmap pixmap;
    int xPos;
    int yPos;
    qreal pressure;
    QString typeDevice;
};

#endif // CANVAS_H
