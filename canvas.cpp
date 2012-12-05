#include "mainwindow.h"
#include "canvas.h"

Canvas::Canvas(BrushEngine *globalBrush)
{
    int widthScreen = qApp->desktop()->width();
    int heigthScreen = qApp->desktop()->height();
    pixmap = new QPixmap(widthScreen, heigthScreen);
    pixmap->fill(Qt::white);
    setAutoFillBackground(true);
    brush = globalBrush;
    connect(brush, SIGNAL(sizeBrushSignal()), this, SLOT(drawCursorSlot()));
    drawCursorSlot();
}

void Canvas::drawCursorSlot()
{
    int sizeBrush = brush->diameterBrush();
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

void Canvas::mouseMoveEvent(QMouseEvent *event)
{
    positionCursor.setX(event->x());
    positionCursor.setY(event->y());
    pressurePen = 1.0;
    typeInputDevice = "Mouse";
    brush->paint(pixmap, positionCursor, pressurePen);
    update();

    emit inputEventSignal();
}

void Canvas::mousePressEvent(QMouseEvent *event)
{
    positionCursor.setX(event->x());
    positionCursor.setY(event->y());
    pressurePen = 1.0;
    typeInputDevice = "Mouse";
    brush->paint(pixmap, positionCursor, pressurePen);
    update();

    emit inputEventSignal();
}

void Canvas::mouseReleaseEvent(QMouseEvent *)
{
    brush->setTouch(false);
}

void Canvas::tabletEvent(QTabletEvent *event)
{
    positionCursor.setX(event->x());
    positionCursor.setY(event->y());
    typeInputDevice = "Stylus";
    pressurePen = event->pressure();
    if (pressurePen > 0)
        brush->paint(pixmap, positionCursor, pressurePen);
    else
        brush->setTouch(false);
    update();

    emit inputEventSignal();
}

void Canvas::clearCanvasSlot()
{
    pixmap->fill(Qt::white);
    update();
}

void Canvas::leaveEvent(QEvent *)
{
    //qDebug() << "leave";
}

void Canvas::enterEvent(QEvent *)
{
    //qDebug() << "enter";
}


