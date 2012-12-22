#ifndef CANVAS_H
#define CANVAS_H

#include <QtGui>
#include "brushengine.h"

//class Canvas : public QWidget
class Canvas : public QGraphicsView
{
    Q_OBJECT

public:
    Canvas(BrushEngine *globalBrush);
    inline QPoint posCursor() {return positionCursor;}
    inline qreal pressure() {return pressurePen;}
    inline QString typeDevice() {return typeInputDevice;}
    inline QPixmap* surface() {return pixmap;}
    inline QPixmap prevSurface() {return prevPixmap;}
    inline void setSurface(QPixmap *surface) {*pixmap = *surface;}
    inline void updatePixmap() {pixmapItem->setPixmap(*pixmap);;}

protected:
    //void paintEvent(QPaintEvent*);
    void mouseMoveEvent(QMouseEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *);
    void tabletEvent(QTabletEvent *event);
    void keyPressEvent(QKeyEvent *event);
    void keyReleaseEvent(QKeyEvent *event);
    void leaveEvent(QEvent *);
    void enterEvent(QEvent *);

signals:
    void inputEventSignal();
    void startPaintSignal();
    
public slots:
    void drawCursorSlot();

private:
    void drawPixmap();
    void scrollCanvas();

    QGraphicsScene *scene;
    QGraphicsView *graphicsView;
    QGraphicsPixmapItem *pixmapItem;

    BrushEngine *brush;
    QPixmap *pixmap;
    QPixmap prevPixmap;
    QPoint positionCursor;
    QPoint prevPositionCursor;
    qreal pressurePen;
    QString typeInputDevice;
    bool spacePress;
};

#endif // CANVAS_H
