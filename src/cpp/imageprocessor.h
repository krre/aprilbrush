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

#ifndef IMAGEPROCESSOR_H
#define IMAGEPROCESSOR_H

#include <QObject>
#include <QPixmap>
#include <QPainter>
#include <QVariantList>
#include <QDebug>

class ImageProcessor : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString layerId READ layerId WRITE setlayerId)

public:
    explicit ImageProcessor();

    Q_INVOKABLE void addPixmap(const QString layerId, const QSize size, const QColor color);
    Q_INVOKABLE void deletePixmap(const QString layerId);
    Q_INVOKABLE void setPixmapArea(const QPoint startPos, const QByteArray area, const QString layerId);
    Q_INVOKABLE void makePng(const QString path, const QVariantList layerIdList);
    Q_INVOKABLE void fillColor(const QString layerId, const QColor color) { m_pixmapHash[layerId]->fill(color); }
    Q_INVOKABLE QColor pickColor(const QPoint point, const QVariantList layerIdList);
    Q_INVOKABLE QVariantList mergePixmap(const QVariantList layerIdList);

    QHash<QString, QPixmap*> pixmapHash() { return m_pixmapHash; }
    QString layerId() const { return m_layerId; }
    void setlayerId(QString arg) { if (m_layerId != arg) m_layerId = arg; }

private:
    QPixmap unionPixmaps(QVariantList layerIdList);

    QPixmap *pixmap;
    QHash<QString, QPixmap*> m_pixmapHash;
    QString m_layerId;
};

#endif // IMAGEPROCESSOR_H
