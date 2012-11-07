#include "mainwindow.h"
#include "canvas.h"

Canvas::Canvas(BrushEngine *globalBrush)
{
    QPixmap newPixmap = QPixmap(1000, 500);
    newPixmap.fill(Qt::white);
    QPainter painter(&newPixmap);
    if (!pixmap.isNull())
        painter.drawPixmap(0, 0, pixmap);
    painter.end();
    pixmap = newPixmap;
    setAutoFillBackground(true);
    nowPos.setX(0);
    nowPos.setY(0);
    brush = globalBrush;
}

void Canvas::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.drawPixmap(0, 0, pixmap);
}

void  Canvas::mouseMoveEvent(QMouseEvent *event)
{
    prevPos = nowPos;
    nowPos.setX(event->x());
    nowPos.setY(event->y());
    typeDevice = "Mouse";
    emit inputEvent();
    brush->paint(&pixmap, prevPos, nowPos, 1.0, 1.0);
    update();
}

void  Canvas::mousePressEvent(QMouseEvent *event)
{
    prevPos.setX(0);
    prevPos.setY(0);
    nowPos.setX(event->x());
    nowPos.setY(event->y());

    typeDevice = "Mouse";
    emit inputEvent();

    brush->paint(&pixmap, prevPos, nowPos, 1.0, 1.0);
    update();
}

void Canvas::tabletEvent(QTabletEvent *event)
{
/*    xPrevPos = xPos;
    xPos = event->x();
    yPrevPos = yPos;
    yPos = event->y();
    typeDevice = "Stylus";
    pressurePrev = pressure;
    pressure = event->pressure();
    emit inputEvent();

    if (pressure > 0)
        brush->paint(&pixmap, xPos, xPrevPos, yPos, yPrevPos, pressure, pressurePrev);
*/
    update();
}

void Canvas::clearCanvas()
{
    pixmap.fill(Qt::white);
    update();
}

