#include "orawriteread.h"

OraWriteRead::OraWriteRead()
{
}

void OraWriteRead::oraWrite(QVariantList paintedItemList)
{
    qDebug() << paintedItemList;
    PaintedItem *paintedItem;
    for (int i = 0; i < paintedItemList.length(); i++)
    {
        QVariant v = paintedItemList.at(i);

        paintedItem = v.value<PaintedItem*>();
        QString path;
        path = QString("D:/pix-%1.png").arg(i, 2, 10, QChar('0'));
        paintedItem->pixmapItem.save(path);
    }
}
