#ifndef CANVAS_H
#define CANVAS_H

#include <QtWidgets>
#include "brushengine.h"

//class Canvas : public QWidget
class Canvas : public QGraphicsView
{
    Q_OBJECT

public:
    Canvas(BrushEngine *globalBrush);
    ~Canvas();
    inline QString name() {return nameCanvas;}
    inline void setName(QString name) {nameCanvas = name;}
    inline QString path() {return pathCanvas;}
    inline void setPath(QString path) {pathCanvas = path;}
    inline QPoint posCursor() {return positionCursor;}
    inline qreal pressure() {return pressurePen;}
    inline QString typeDevice() {return typeInputDevice;}
    inline QPixmap* surface() {return pixmap;}
    inline QPixmap prevSurface() {return prevPixmap;}
    inline void setSurface(QPixmap *surface) {*pixmap = *surface;}
    inline void updatePixmap() {pixmapItem->setPixmap(*pixmap);}
    inline QList<QGraphicsPixmapItem*> layers() {return layerList;}

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

    QString nameCanvas;
    QString pathCanvas;

    QGraphicsScene *scene;
    //QGraphicsView *graphicsView;
    //QGraphicsRectItem *backgroundItem;
    QGraphicsPixmapItem *backgroundItem;
    QGraphicsPixmapItem *pixmapItem;

    BrushEngine *brush;
    QPixmap *pixmap;
    QPixmap *backgroundPixmap;
    QPixmap prevPixmap;
    QPoint positionCursor;
    QPoint prevPositionCursor;
    qreal pressurePen;
    QString typeInputDevice;
    bool spacePress;
    QList<QGraphicsPixmapItem*> layerList;
};

#endif // CANVAS_H
