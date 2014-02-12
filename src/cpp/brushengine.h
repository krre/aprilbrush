/* AprilBrush - Digital Painting Software
 * Copyright (C) 2012-2013 Vladimir Zarypov <krre31@gmail.com>
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

#ifndef BRUSHENGINE_H
#define BRUSHENGINE_H

#include "imageprocessor.h"

class BrushEngine : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int size READ size WRITE setSize)
    Q_PROPERTY(int spacing READ spacing WRITE setSpacing)
    Q_PROPERTY(int hardness READ hardness WRITE setHardness)
    Q_PROPERTY(QColor color READ color WRITE setColor)
    Q_PROPERTY(int opacity READ opacity WRITE setOpacity)
    Q_PROPERTY(int roundness READ roundness WRITE setRoundness)
    Q_PROPERTY(int angle READ angle WRITE setAngle)
    Q_PROPERTY(int jitter READ jitter WRITE setJitter)
    Q_PROPERTY(bool eraser READ eraser WRITE setEraser)
    Q_PROPERTY(QString layerId READ layerId WRITE setLayerId)
    Q_PROPERTY(ImageProcessor* imageProcessor READ imageProcessor WRITE setImageProcessor)

public:
    BrushEngine();

    Q_INVOKABLE void paintDab(QPoint nowPoint, qreal pressure);
    Q_INVOKABLE void setTouch(QPoint nowPoint);
    Q_INVOKABLE void setUnTouch();
    Q_INVOKABLE void clear() { pixmap->fill(QColor(0, 0, 0, 0)); }
    Q_INVOKABLE QPoint startPos() { return minPoint; }
    Q_INVOKABLE QByteArray undoArea() { return undoByteArray; }
    Q_INVOKABLE QByteArray redoArea() { return redoByteArray; }
    Q_INVOKABLE QByteArray currentArea() { return compressPixmap(*pixmap); }
    ImageProcessor* imageProcessor() const { return m_imageProcessor; }

    QString layerId() const { return m_layerId; }

signals:
    void paintDone();

public slots:
    void setLayerId(QString arg);
    void setImageProcessor(ImageProcessor* arg) { m_imageProcessor = arg; }

private:
    int size() {return m_size;}
    void setSize(int size) { m_size = size; }

    int spacing() { return m_spacing; }
    void setSpacing(int spacing) { m_spacing = spacing; }

    int hardness() { return m_hardness; }
    void setHardness(int hardness) { m_hardness = hardness; }

    QColor color() { return m_color; }
    void setColor(QColor color) { m_color = color; }

    int opacity() { return m_opacity; }
    void setOpacity(int opacity) { m_opacity = opacity; }

    int roundness() { return m_roundness; }
    void setRoundness(int roundness) { m_roundness = roundness; }

    int angle() { return m_angle; }
    void setAngle(int angle) { m_angle = angle; }

    int jitter() { return m_jitter; }
    void setJitter(int jitter) { m_jitter = jitter; }

    bool eraser() { return m_eraser; }
    void setEraser(bool eraser) { m_eraser = eraser; }

    QByteArray compressPixmap(QPixmap pixmap);

    int m_size;
    int m_spacing;
    int m_hardness;
    int m_roundness;
    int m_angle;
    int m_jitter;
    QColor m_color;
    int m_opacity;
    bool m_eraser;
    QPixmap *prevPixmap;
    QByteArray undoByteArray;
    QByteArray redoByteArray;

    QPointF prevPoint;
    QPoint minPoint;
    QPoint maxPoint;
    QString m_layerId;
    QPixmap *pixmap;
    ImageProcessor *m_imageProcessor;
};

#endif // BRUSHENGINE_H
