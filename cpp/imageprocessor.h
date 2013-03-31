#ifndef IMAGEPROCESSOR_H
#define IMAGEPROCESSOR_H

#include <QObject>
#include <QtGui>

class ImageProcessor : public QObject
{
    Q_OBJECT

public:
    explicit ImageProcessor();

    Q_INVOKABLE void addPixmap(const QString id, const QSize size, const QColor color);
    Q_INVOKABLE void deletePixmap(const QString id);
    QHash<QString, QPixmap*> pixmapHash() { return m_pixmapHash; }

signals:
    
public slots:

private:
    QPixmap *pixmap;
    QHash<QString, QPixmap*> m_pixmapHash;
    
};

#endif // IMAGEPROCESSOR_H
