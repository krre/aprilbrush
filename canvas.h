#ifndef CANVAS_H
#define CANVAS_H

#include <QtGui>

class Canvas : public QWidget
{
    Q_OBJECT
public:
    Canvas();

protected:
    void paintEvent(QPaintEvent*);
    void mouseMoveEvent(QMouseEvent *event);
    //void tabletEvent(QTabletEvent *event);
    
signals:
    
public slots:

private:
    QPixmap pixmap;

};

#endif // CANVAS_H
