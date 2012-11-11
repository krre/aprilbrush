#include "mainwindow.h"
#include "canvas.h"

Canvas::Canvas(BrushEngine *globalBrush)
{
    pixmap = new QPixmap(1000, 500);
    pixmap->fill(Qt::white);
    setAutoFillBackground(true);
    brush = globalBrush;
    connect(brush, SIGNAL(sizeBrushSignal()), this, SLOT(drawCursorSlot()));
    drawCursorSlot();
}

void Canvas::drawCursorSlot()
{
    int sizeBrush = brush->getSizeBrush();
    QPixmap pixmap(sizeBrush, sizeBrush);
    pixmap.fill(QColor(255, 255, 255, 0));
    QPainter painter(&pixmap);
    painter.setRenderHint(QPainter::Antialiasing, true);
    painter.setBrush(Qt::NoBrush);
    painter.setPen(QColor(0, 0, 0, 200));
    painter.drawEllipse(0, 0, sizeBrush, sizeBrush);
    painter.setPen(QColor(255, 255, 255, 200));
    painter.drawEllipse(1, 1, sizeBrush - 2, sizeBrush - 2);
    setCursor(pixmap);
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


