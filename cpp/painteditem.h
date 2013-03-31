#ifndef PAINTSPACE_H
#define PAINTSPACE_H

#include <QQuickPaintedItem>
#include <QtGui>
#include "imageprocessor.h"

class PaintedItem : public QQuickPaintedItem
{
    Q_OBJECT
    Q_PROPERTY(ImageProcessor* imageProcessor READ imageProcessor WRITE setImageProcessor)

public:
    PaintedItem(QQuickItem *parent = 0);
    void paint(QPainter *painter);
    ImageProcessor* imageProcessor() const { return m_imageProcessor; }

public slots:
    void setImageProcessor(ImageProcessor* arg) { m_imageProcessor = arg; }

private:
    QPixmap *pixmap;
    ImageProcessor *m_imageProcessor;
};

#endif // PAINTSPACE_H
