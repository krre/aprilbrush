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

void Canvas::tabletEvent(QTabletEvent *event)
{
    qreal pressure = event->pressure();
    if (pressure > 0)
    {
        QPainter painter(&pixmap);
        painter.setRenderHint(QPainter::Antialiasing, true);
        painter.setPen(Qt::NoPen);
        painter.setBrush(QBrush(QColor(0, 255, 0, int(pressure * 255)), Qt::SolidPattern));
        painter.drawEllipse(event->x(), event->y(), 10, 10);
    }
    if (testID->isVisible())
        testID->setInputValues(tr("Stylus"), event->x(), event->y(), pressure);

    update();
}

void Canvas::clearAction()
{
    pixmap.fill(Qt::white);
    update();
}

