/* AprilBrush - Digital Painting Software
 * Copyright (C) 2012-2013 Vladimir Zarypov <krre@mail.ru>
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

#ifndef ORAWRITEREAD_H
#define ORAWRITEREAD_H

#include "imageprocessor.h"
#include "qzip/qzipreader_p.h"
#include "qzip/qzipwriter_p.h"

#include <QPixmap>
#include <QXmlStreamReader>
#include <QXmlStreamWriter>
#include <QBuffer>
#include <QMap>
#include <QVariant>

class OpenRaster : public QObject
{
    Q_OBJECT
    Q_PROPERTY(ImageProcessor* imageProcessor READ imageProcessor WRITE setImageProcessor)

public:
    OpenRaster();
    Q_INVOKABLE void write(const QString oraPath, const QSize imageSize, const QVariantList layerList);
    Q_INVOKABLE QVariantList readAttributes(const QString oraPath);
    Q_INVOKABLE void readPixmap(const QString oraPath, const QString pngPath, const QString layerId);

    ImageProcessor* imageProcessor() const { return m_imageProcessor; }

public slots:
    void setImageProcessor(ImageProcessor* arg) { m_imageProcessor = arg; }


private:
    QList<QString> oraLayersNameList;
    QList<QPixmap> oraPixmapsList;
    ImageProcessor *m_imageProcessor;
};

#endif // ORAWRITEREAD_H
