#include "mainwindow.h"
#include "canvas.h"

Canvas::Canvas()
{
    QPixmap newPixmap = QPixmap(1000, 500);
    newPixmap.fill(Qt::white);
    QPainter painter(&newPixmap);
    if (!pixmap.isNull())
        painter.drawPixmap(0, 0, pixmap);
    painter.end();
    pixmap = newPixmap;
    setAutoFillBackground(true);
}

void Canvas::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.drawPixmap(0, 0, pixmap);
}

void  Canvas::mouseMoveEvent(QMouseEvent *event)
{
    qDebug() << "Mouse: Pos X: " << event->x() << " Pos Y: " << event->y();
    QPainter painter(&pixmap);
    painter.setRenderHint(QPainter::Antialiasing, true);
    painter.setPen(Qt::NoPen);
    painter.setBrush(QBrush(Qt::blue, Qt::SolidPattern));
    painter.drawEllipse(event->x(), event->y(), 10, 10);
    update();
}
/*
void Canvas::tabletEvent(QTabletEvent *event)
{

    //qDebug() << "Tablet: " << event->device() << "Pos X: " << event->x() << " Pos Y: " << event->y()
    //qDebug() << "Pos X: " << event->x() << " Pos Y: " << event->y()
    //    << " Pressure: " << event->pressure();
    //qDebug() << event->type();
    //event->accept();
}
*/
