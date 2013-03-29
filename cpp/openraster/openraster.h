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
    Q_INVOKABLE void readAttributes(const QString oraPath);
    //Q_INVOKABLE void readPixmap(const QString oraPath, const QString layerName);
    Q_INVOKABLE QList<QString> layersNameList() { return oraLayersNameList; }
    Q_INVOKABLE void setPixmap(PaintedItem *paintedItem, int index);
    //Q_INVOKABLE QList<QPixmap*> pixmapsList() { return oraPixmapsList; }


private:
    QList<QString> oraLayersNameList;
    QList<QPixmap> oraPixmapsList;
};

#endif // ORAWRITEREAD_H
