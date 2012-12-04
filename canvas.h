#ifndef CANVAS_H
#define CANVAS_H

#include <QtGui>
#include "brushengine.h"

class Canvas : public QWidget
{
    Q_OBJECT

public:
    Canvas(BrushEngine *globalBrush);
    inline QPoint posCursor() {return positionCursor;}
    inline qreal pressure() {return pressurePen;}
    inline QString typeDevice() {return typeInputDevice;}

protected:
    void paintEvent(QPaintEvent*);
    void mouseMoveEvent(QMouseEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *);
    void tabletEvent(QTabletEvent *event);
    void leaveEvent(QEvent *);
    void enterEvent(QEvent *);

signals:
    void inputEventSignal();
    
public slots:
    void clearCanvasSlot();
    void drawCursorSlot();

private:

    BrushEngine *brush;
    QPixmap *pixmap;
    QPoint positionCursor;
    qreal pressurePen;
    QString typeInputDevice;
};

#endif // CANVAS_H
