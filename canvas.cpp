#include "mainwindow.h"
#include "canvas.h"

Canvas::Canvas(BrushEngine *globalBrush)
{
    int widthScreen = qApp->desktop()->width();
    int heigthScreen = qApp->desktop()->height();
    //int widthScreen = 500;
    //int heigthScreen = 500;
    pixmap = new QPixmap(widthScreen, heigthScreen);
    pixmap->fill(Qt::white);
    setAutoFillBackground(true);
    brush = globalBrush;
    connect(brush, SIGNAL(sizeBrushSignal()), this, SLOT(drawCursorSlot()));
    drawCursorSlot();
    spacePress = false;

    //setFocus();
    //setFocusPolicy(Qt::ClickFocus);
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

    if (spacePress)
    {
        scrollCanvas();
    }
    else
    {
        brush->paint(pixmap, positionCursor, pressurePen);
    }

    update();

    emit inputEventSignal();
}

void Canvas::mousePressEvent(QMouseEvent *event)
{
    if (!spacePress)
    {
        prevPixmap = *pixmap;
        positionCursor.setX(event->x());
        positionCursor.setY(event->y());
        pressurePen = 1.0;
        typeInputDevice = "Mouse";
        brush->paint(pixmap, positionCursor, pressurePen);
    }
    update();

    emit inputEventSignal();
}

void Canvas::mouseReleaseEvent(QMouseEvent *)
{
    if (!spacePress)
    {
        brush->setTouch(false);
        emit startPaintSignal();
    }
}

void Canvas::tabletEvent(QTabletEvent *event)
{
    positionCursor.setX(event->x());
    positionCursor.setY(event->y());
    typeInputDevice = "Stylus";
    pressurePen = event->pressure();

    switch (event->type())
    {
        case (QEvent::TabletPress):
        {
            if (!spacePress)
            {
                prevPixmap = *pixmap;
            }
            break;
        }
        case (QEvent::TabletRelease):
        {
            if (!spacePress)
            {
                emit startPaintSignal();
                brush->setTouch(false);
            }
            break;
        }
        case (QEvent::TabletMove):
        {
            if (spacePress && (pressurePen > 0))
            {                
                scrollCanvas();
            }
            break;
        }

        default:
            break;
    }

    if (pressurePen > 0 && !spacePress)
        brush->paint(pixmap, positionCursor, pressurePen);

    update();

    emit inputEventSignal();
}

void Canvas::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Space)
        prevPositionCursor = positionCursor;
        spacePress = true;
}

void Canvas::keyReleaseEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Space)
        spacePress = false;
}

void Canvas::scrollCanvas()
{
    int dx = positionCursor.x() - prevPositionCursor.x();
    int dy = positionCursor.y() - prevPositionCursor.y();
    pixmap->scroll(dx, dy, 0, 0, qApp->desktop()->width(), qApp->desktop()->height());
    //pixmap->scroll(dx, dy, 0, 0, 500, 500);
    prevPositionCursor = positionCursor;
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


