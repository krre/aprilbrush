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
    brush = globalBrush;
}

void Canvas::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.drawPixmap(0, 0, pixmap);
}

void  Canvas::mouseMoveEvent(QMouseEvent *event)
{
    xPos = event->x();
    yPos = event->y();
    typeDevice = "Mouse";
    pressure = 1.0;
    emit inputEvent();
    brush->paint(&pixmap, xPos, yPos, pressure);
    update();
}

void  Canvas::mousePressEvent(QMouseEvent *event)
{
    xPos = event->x();
    yPos = event->y();
    typeDevice = "Mouse";
    pressure = 1.0;
    emit inputEvent();
    brush->paint(&pixmap, xPos, yPos, pressure);
    update();
}

void Canvas::tabletEvent(QTabletEvent *event)
{
    xPos = event->x();
    yPos = event->y();
    typeDevice = "Stylus";
    pressure = event->pressure();
    emit inputEvent();

    if (pressure > 0)
        brush->paint(&pixmap, xPos, yPos, pressure);

    update();
}

void Canvas::clearAction()
{
    pixmap.fill(Qt::white);
    update();
}

