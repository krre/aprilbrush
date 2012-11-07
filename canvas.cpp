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
    pressure = 1.0;
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
    pressure = 1.0;
    typeDevice = "Mouse";
    emit inputEvent();
    brush->paint(&pixmap, prevPos, nowPos, pressure, pressure);
    update();
}

void  Canvas::mousePressEvent(QMouseEvent *event)
{
    prevPos.setX(0);
    prevPos.setY(0);
    nowPos.setX(event->x());
    nowPos.setY(event->y());
    pressure = 1.0;

    typeDevice = "Mouse";
    emit inputEvent();

    brush->paint(&pixmap, prevPos, nowPos, pressure, pressure);
    update();
}

void Canvas::tabletEvent(QTabletEvent *event)
{
    prevPos = nowPos;
    nowPos.setX(event->x());
    nowPos.setY(event->y());
    typeDevice = "Stylus";
    prevPressure = pressure;
    pressure = event->pressure();
    emit inputEvent();

    if (pressure > 0)
        brush->paint(&pixmap, prevPos, nowPos, prevPressure, pressure);

    update();
}

void Canvas::clearCanvas()
{
    pixmap.fill(Qt::white);
    update();
}

