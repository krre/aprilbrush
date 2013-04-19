#include "imageprocessor.h"

#include <QImage>
#include <QBuffer>

ImageProcessor::ImageProcessor()
{
}

void ImageProcessor::addPixmap(const QString layerId, const QSize size, const QColor color)
{

    pixmap = new QPixmap(size);
#ifdef QT_NO_DEBUG
    // This line causes crash in debug mode on start application in Windows
    pixmap->fill(color);
#endif
    m_pixmapHash.insert(layerId, pixmap);
}

void ImageProcessor::deletePixmap(const QString layerId)
{
    pixmap  = m_pixmapHash[layerId];
    delete pixmap;
    m_pixmapHash.remove(layerId);
}

void ImageProcessor::setPixmapArea(const QPoint startPos, const QByteArray area, const QString layerId)
{
    QPixmap areaPixmap;
    areaPixmap.loadFromData(area);
    pixmap  = m_pixmapHash[layerId];

    QPainter painter(pixmap);
    painter.setCompositionMode(QPainter::CompositionMode_Source);
    painter.fillRect(QRect(startPos, areaPixmap.size()), Qt::transparent);
    painter.setCompositionMode(QPainter::CompositionMode_SourceOver);
    painter.drawPixmap(startPos.x(), startPos.y(), areaPixmap);
}

void ImageProcessor::makePng(const QString path, const QVariantList layerIdList)
{
    unionPixmaps(layerIdList).save(path);
}

QColor ImageProcessor::pickColor(const QPoint point, const QVariantList layerIdList)
{
    QImage image = QPixmap(unionPixmaps(layerIdList)).toImage();
    QColor color;
    return color.fromRgb(image.pixel(point));
}

QVariantList ImageProcessor::mergePixmap(const QVariantList layerIdList)
{
    QString layerId1 = layerIdList.at(0).toString();
    QString layerId2 = layerIdList.at(1).toString();
    QPixmap pixmap1 = *m_pixmapHash[layerId1];
    QPixmap pixmap2 = *m_pixmapHash[layerId2];

    QByteArray byteArray;
    QVariantList pixmapList;

    QBuffer buffer(&byteArray);
    buffer.open(QIODevice::WriteOnly);
    pixmap1.save(&buffer, "TIF");
    buffer.close();
    pixmapList.append(byteArray);

    buffer.setBuffer(&byteArray);
    buffer.open(QIODevice::WriteOnly);
    pixmap2.save(&buffer, "TIF");
    buffer.close();
    pixmapList.append(byteArray);

    QPainter painter(m_pixmapHash[layerId2]);
    painter.drawPixmap(0, 0, pixmap1);

    return pixmapList;
}

QPixmap ImageProcessor::unionPixmaps(QVariantList layerIdList)
{
    QPixmap *pixmap;
    QPixmap joinPixmap;
    for (int i = layerIdList.count() - 1; i >= 0; i--)
    {
        QString layerId = layerIdList.at(i).toString();
        pixmap = m_pixmapHash[layerId];
        if (joinPixmap.isNull())
        {
            joinPixmap = QPixmap(pixmap->width(), pixmap->height());
            joinPixmap.fill(Qt::transparent);
        }
        QPainter painter(&joinPixmap);
        painter.drawPixmap(0, 0, *pixmap);
    }
    return joinPixmap;
}


