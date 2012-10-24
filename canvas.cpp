#include "mainwindow.h"
#include "widgets/testinputdevice.h"
#include "canvas.h"

Canvas::Canvas(TestInputDevice *testIDWindow)
{
    QPixmap newPixmap = QPixmap(1000, 500);
    newPixmap.fill(Qt::white);
    QPainter painter(&newPixmap);
    if (!pixmap.isNull())
        painter.drawPixmap(0, 0, pixmap);
    painter.end();
    pixmap = newPixmap;
    setAutoFillBackground(true);
    testID = testIDWindow;
}

void Canvas::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.drawPixmap(0, 0, pixmap);
}

void  Canvas::mouseMoveEvent(QMouseEvent *event)
{
    QPainter painter(&pixmap);
    painter.setRenderHint(QPainter::Antialiasing, true);
    painter.setPen(Qt::NoPen);
    painter.setBrush(QBrush(Qt::blue, Qt::SolidPattern));
    painter.drawEllipse(event->x(), event->y(), 10, 10);

    if (testID->isVisible())
        testID->setInputValues(tr("Mouse"), event->x(), event->y(), 1.0);

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
