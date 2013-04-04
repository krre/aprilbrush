#ifndef IMAGEPROCESSOR_H
#define IMAGEPROCESSOR_H

#include <QObject>
#include <QPixmap>
#include <QPainter>
#include <QVariantList>

class ImageProcessor : public QObject
{
    Q_OBJECT

public:
    explicit ImageProcessor();

    Q_INVOKABLE void addPixmap(const QString layerId, const QSize size, const QColor color);
    Q_INVOKABLE void deletePixmap(const QString layerId);
    Q_INVOKABLE void setPixmapArea(const QPoint startPos, const QByteArray area, const QString layerId);
    Q_INVOKABLE void makePng(const QString path, const QVariantList layerIdList);
    Q_INVOKABLE void fillColor(const QString layerId, const QColor color) { m_pixmapHash[layerId]->fill(color); }
    QHash<QString, QPixmap*> pixmapHash() { return m_pixmapHash; }

signals:
    
public slots:

private:
    QPixmap *pixmap;
    QHash<QString, QPixmap*> m_pixmapHash;
};

#endif // IMAGEPROCESSOR_H
