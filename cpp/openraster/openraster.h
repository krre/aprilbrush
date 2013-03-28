#ifndef ORAWRITEREAD_H
#define ORAWRITEREAD_H
#include <QtGui>
#include "../painteditem.h"
#include "qzip/qzipreader_p.h"
#include "qzip/qzipwriter_p.h"

class OpenRaster : public QObject
{
    Q_OBJECT

public:
    OpenRaster();
    Q_INVOKABLE void write(const QString oraPath, const QSize imageSize, const QVariantList paintedItemList, const QVariantList layersNameList);
};

#endif // ORAWRITEREAD_H
