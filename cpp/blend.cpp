#include "blend.h"

Blend::Blend(QObject *parent) :
    QObject(parent)
{
}

void Blend::alphaMax(const QImage& src, QImage& dst, const QPointF& coord, qreal factor)
{
    QColor srcColor;
    QColor dstColor;
    qreal alpha;
    qreal x = qMax(0.0, qMin(coord.x() - src.width() / 2.0, dst.width() * 1.0));
    qreal y = qMax(0.0, qMin(coord.y() - src.height() / 2.0, dst.height() * 1.0));
    for (int i = 0; i < src.width(); i++) {
        for(int j = 0; j < src.height(); j++) {
            srcColor = QColor::fromRgba(src.pixel(i, j));
            dstColor = QColor::fromRgba(dst.pixel(i + x, j + y));
//            if (srcColor.alpha() > dstColor.alpha()) {
//                dst.setPixel(i + coord.x(), j + coord.y(), srcColor.rgba());
//            }
            // ALPHA OVER: resAlpha = srcAlpha + dstAlpha * (1 - srcAplha)
            qreal alpha = srcColor.alphaF() * factor + dstColor.alphaF() * (1 - srcColor.alphaF());
//            qDebug() << srcColor.alpha() << dstColor.alpha() << alpha;
//            alpha = srcColor.alphaF() * factor;
            if (alpha) {
                srcColor.setAlphaF(alpha);
                dst.setPixel(i + x, j + y, srcColor.rgba());
            }
        }
    }
}
