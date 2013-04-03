#ifndef PAINTSPACE_H
#define PAINTSPACE_H

#include "imageprocessor.h"

#include <QQuickPaintedItem>

class PaintedItem : public QQuickPaintedItem
{
    Q_OBJECT
    Q_PROPERTY(ImageProcessor* imageProcessor READ imageProcessor WRITE setImageProcessor)

public:
    PaintedItem(QQuickItem *parent = 0);
    void paint(QPainter *painter);
    ImageProcessor* imageProcessor() const { return m_imageProcessor; }
    Q_INVOKABLE void setItemCursor(const QString name, const qreal size);
    Q_INVOKABLE void unSetItemCursor();

public slots:
    void setImageProcessor(ImageProcessor* arg) { m_imageProcessor = arg; }

private:
    QPixmap *pixmap;
    ImageProcessor *m_imageProcessor;
};

#endif // PAINTSPACE_H
