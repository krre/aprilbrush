#include "imageprocessor.h"

#include <QDebug>

ImageProcessor::ImageProcessor()
{
}

void ImageProcessor::addPixmap(const QString layerId, const QSize size, const QColor color)
{

    pixmap = new QPixmap(size);
    //qDebug() << *pixmap << color;
    //pixmap->fill(color);

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
    QPixmap *pixmap;
    QPixmap exportPixmap;
    for (int i = layerIdList.count() - 1; i >= 0; i--){
        QString layerId = layerIdList.at(i).toString();
        pixmap = m_pixmapHash[layerId];
        if (exportPixmap.isNull())
        {
            exportPixmap = QPixmap(pixmap->width(), pixmap->height());
            exportPixmap.fill(Qt::transparent);
        }
        QPainter painter(&exportPixmap);
        painter.drawPixmap(0, 0, *pixmap);
    }
    exportPixmap.save(path);
}
