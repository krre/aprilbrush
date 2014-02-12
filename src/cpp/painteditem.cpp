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

#include "painteditem.h"
#include <QDebug>
#include <QCursor>

PaintedItem::PaintedItem(QQuickItem *parent) : QQuickPaintedItem(parent)
{
    pixmap = 0;
    //setRenderTarget(QQuickPaintedItem::FramebufferObject);
}

void PaintedItem::paint(QPainter *painter)
{
    if (!pixmap)
        pixmap = m_imageProcessor->pixmapHash()[objectName()];

    painter->drawPixmap(0, 0, *pixmap);
}

void PaintedItem::setItemCursor(const QString name, const qreal size)
{
    //qDebug() << name;
    if (name == "Paint")
    {

        int sizeBrush = size;
          // Size of the cursor should not be very small
        if (sizeBrush < 3)
              sizeBrush = 3;

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
        return;
    }

    if (name == "OpenHand")
    {
        QCursor cursor = QCursor(Qt::OpenHandCursor);
        setCursor(cursor);
        return;
    }

    if (name == "ClosedHand")
    {
        QCursor cursor = QCursor(Qt::ClosedHandCursor);
        setCursor(cursor);
        return;
    }
}

void PaintedItem::unSetItemCursor()
{
    QCursor cursor = QCursor(Qt::ArrowCursor);
    setCursor(cursor);
    //qDebug() << "unset";
}
