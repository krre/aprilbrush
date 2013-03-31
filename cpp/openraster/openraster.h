#ifndef ORAWRITEREAD_H
#define ORAWRITEREAD_H
#include <QtGui>
#include "../imageprocessor.h"
#include "qzip/qzipreader_p.h"
#include "qzip/qzipwriter_p.h"

class OpenRaster : public QObject
{
    Q_OBJECT
    Q_PROPERTY(ImageProcessor* imageProcessor READ imageProcessor WRITE setImageProcessor)

public:
    OpenRaster();
    Q_INVOKABLE void write(const QString oraPath, const QSize imageSize, const QVariantList layerList);
    Q_INVOKABLE void readAttributes(const QString oraPath);
    //Q_INVOKABLE void readPixmap(const QString oraPath, const QString layerName);

    ImageProcessor* imageProcessor() const { return m_imageProcessor; }

public slots:
    void setImageProcessor(ImageProcessor* arg) { m_imageProcessor = arg; }


private:
    QList<QString> oraLayersNameList;
    QList<QPixmap> oraPixmapsList;
    ImageProcessor *m_imageProcessor;
};

#endif // ORAWRITEREAD_H
