#ifndef ORAWRITEREAD_H
#define ORAWRITEREAD_H
#include <QtGui>
#include "../painteditem.h"

class OraWriteRead : public QObject
{
    Q_OBJECT

public:
    OraWriteRead();
    Q_INVOKABLE void oraWrite(QVariantList paintedItemList);
};

#endif // ORAWRITEREAD_H
