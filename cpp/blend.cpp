#include "blend.h"

Blend::Blend(QObject *parent) :
    QObject(parent)
{
}

void Blend::alphaMax(const QImage& src, QImage& dst, const QPointF& coord, qreal factor)
{
    qDebug() << src << dst << coord << factor;
    src.save("d:/src.png");
    int c = 0;

    for (int i = 0; i < src.width(); i++) {
        for(int j = 0; j < src.height(); j++) {
            QColor srcColor = QColor(src.pixel(i, j));
            QColor dstColor = QColor(dst.pixel(i + coord.x(), j + coord.y()));
            QColor resultColor = srcColor;
            resultColor.setAlpha(qMax(srcColor.alpha(), dstColor.alpha()));
            dst.setPixel(i + coord.x(), j + coord.y(), resultColor.rgba());
//            qDebug() << resultColor << c++;
        }
    }
    dst.save("d:/dst.png");
}
