#include "imageprocessor.h"

#include <QImage>

ImageProcessor::ImageProcessor()
{
}

void ImageProcessor::addPixmap(const QString layerId, const QSize size, const QColor color)
{

    pixmap = new QPixmap(size);
    //qDebug() << *pixmap << color;
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
    areaPixmap.loadFromData(qUncompress(area));
    pixmap  = m_pixmapHash[layerId];

    if ((startPos.x()) != 0 && (startPos.y() != 0))
    {
        QPainter painter(pixmap);
        painter.setCompositionMode(QPainter::CompositionMode_Source);
        painter.fillRect(QRect(startPos, areaPixmap.size()), Qt::transparent);
        painter.setCompositionMode(QPainter::CompositionMode_SourceOver);
        painter.drawPixmap(startPos.x(), startPos.y(), areaPixmap);
    }
    else
        *pixmap = QPixmap(areaPixmap);
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

QPixmap ImageProcessor::unionPixmaps(QVariantList layerIdList)
{
    QPixmap *pixmap;
    QPixmap joinPixmap;
    for (int i = layerIdList.count() - 1; i >= 0; i--){
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
