#include "imageprocessor.h"

ImageProcessor::ImageProcessor()
{
}

void ImageProcessor::addPixmap(const QString id, const QSize size, const QColor color)
{
    pixmap = new QPixmap(size);
    pixmap->fill(color);
    m_pixmapHash.insert(id, pixmap);
}

void ImageProcessor::deletePixmap(const QString id)
{
    pixmap  = m_pixmapHash[id];
    delete pixmap;
    m_pixmapHash.remove(id);
}
