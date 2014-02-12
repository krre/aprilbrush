/* AprilBrush - Digital Painting Software
 * Copyright (C) 2012-2014 Vladimir Zarypov <krre31@gmail.com>
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation;
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 */

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
