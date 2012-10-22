#include "mainwindow.h"
#include "canvas.h"

Canvas::Canvas()
{
    QPixmap newPixmap = QPixmap(width(), height());
    newPixmap.fill(Qt::red);
    QPainter painter(&newPixmap);
    if (!pixmap.isNull())
        painter.drawPixmap(0, 0, pixmap);
    painter.end();
    pixmap = newPixmap;
}

void Canvas::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.drawPixmap(0, 0, pixmap);
}

/*
void  Canvas::mouseMoveEvent(QMouseEvent *event)
{
    qDebug() << "Mouse: Pos X: " << event->x() << " Pos Y: " << event->y();
}

void Canvas::tabletEvent(QTabletEvent *event)
{

    //qDebug() << "Tablet: " << event->device() << "Pos X: " << event->x() << " Pos Y: " << event->y()
    //qDebug() << "Pos X: " << event->x() << " Pos Y: " << event->y()
    //    << " Pressure: " << event->pressure();
    //qDebug() << event->type();
    //event->accept();
}
*/
