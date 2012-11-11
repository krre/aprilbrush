#include "mainwindow.h"
#include "canvas.h"

Canvas::Canvas(BrushEngine *globalBrush)
{
    pixmap = new QPixmap(1000, 500);
    pixmap->fill(Qt::white);
    setAutoFillBackground(true);
    brush = globalBrush;

}

void Canvas::paintEvent(QPaintEvent*)
{
    QPainter painter(this);
    painter.drawPixmap(0, 0, *pixmap);
}

void  Canvas::mouseMoveEvent(QMouseEvent *event)
{
    posCursor.setX(event->x());
    posCursor.setY(event->y());
    pressure = 1.0;
    typeDevice = "Mouse";
    brush->paint(pixmap, posCursor, pressure);
    update();

    emit inputEventSignal();
}

void  Canvas::mousePressEvent(QMouseEvent *event)
{
    posCursor.setX(event->x());
    posCursor.setY(event->y());
    pressure = 1.0;
    typeDevice = "Mouse";
    brush->paint(pixmap, posCursor, pressure);
    update();

    emit inputEventSignal();
}

void Canvas::tabletEvent(QTabletEvent *event)
{
    posCursor.setX(event->x());
    posCursor.setY(event->y());
    typeDevice = "Stylus";
    pressure = event->pressure();
    if (pressure > 0)
        brush->paint(pixmap, posCursor, pressure);
    update();

    emit inputEventSignal();
}

void Canvas::clearCanvasSlot()
{
    pixmap->fill(Qt::white);
    update();
}
