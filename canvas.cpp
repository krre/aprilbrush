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

    globalBrush = new BrushEngine;
}

void Canvas::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.drawPixmap(0, 0, pixmap);
}

void  Canvas::mouseMoveEvent(QMouseEvent *event)
{
    globalBrush->paint(&pixmap, event->x(), event->y(), 1.0);

    if (testID->isVisible())
        testID->setInputValues(tr("Mouse"), event->x(), event->y(), 1.0);

    update();
}

void Canvas::tabletEvent(QTabletEvent *event)
{
    qreal pressure = event->pressure();
    if (pressure > 0)
        globalBrush->paint(&pixmap, event->x(), event->y(), pressure);

    if (testID->isVisible())
        testID->setInputValues(tr("Stylus"), event->x(), event->y(), pressure);

    update();
}

void Canvas::clearAction()
{
    pixmap.fill(Qt::white);
    update();
}

