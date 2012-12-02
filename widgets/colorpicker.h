#ifndef COLORPICKER_H
#define COLORPICKER_H

#include <QtGui>

class ColorPicker : public QWidget
{
    Q_OBJECT

public:
    ColorPicker(QWidget *parent = 0);
    inline QColor color() {return currentPickerColor;}

protected:
    void resizeEvent(QResizeEvent *);
    void paintEvent(QPaintEvent *);
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *);
    void mouseMoveEvent(QMouseEvent *event);
    
signals:
    void colorSignal();
    
public slots:

private:
    void drawWheel();
    void paintWheel();
    void drawTriangle();
    void paintTriangle();
    void setWheelSelector();
    void drawTriangleSelector();
    QColor coordToColor(QPoint coord);
    QPoint colorToCoord(QColor color);

    QImage triangleImage;
    QColor backgroundColor;
    qreal scaleInnerWheel;
    qreal Pi;
    qreal edgeTriangle;
    int diameterWheel;
    int innerRadius;
    int outerRadius;
    qreal hueAngle;
    qreal satValAngle;
    qreal hueColor;
    bool hueGrab;
    bool satValGrab;
    QPointF triangleSelectorPoint;
    QColor currentPickerColor;
};

#endif // COLORPICKER_H
