#ifndef CANVAS_H
#define CANVAS_H

#include <QtGui>
#include "widgets/testinputdevice.h"
#include "brushengine.h"

class Canvas : public QWidget
{
    Q_OBJECT

public:
    Canvas(TestInputDevice *testIDWindow);

protected:
    void paintEvent(QPaintEvent*);
    void mouseMoveEvent(QMouseEvent *event);
    void tabletEvent(QTabletEvent *event);
    
signals:
    
public slots:
    void clearAction();

private:
    QPixmap pixmap;
    TestInputDevice *testID;
    BrushEngine *globalBrush;
};

#endif // CANVAS_H
