#pragma once
#include <QtGui>
#include <QtQuick>
#include <QtQml>

class CanvasItem : public QQuickItem
{
    Q_OBJECT
    Q_PROPERTY(QSize size READ size WRITE setSize NOTIFY sizeChanged)
public:
    CanvasItem();
    ~CanvasItem();
    QSize size() const { return m_size; }
    QPixmap* pixmap() const { return m_pixmap; }
    Q_INVOKABLE void clear();
    Q_INVOKABLE QPointF itemPos(const QPointF& point) { return mapFromScene(point); }

public slots:
    void setSize(QSize size);

signals:
    void sizeChanged(QSize size);

protected:
    QSGNode* updatePaintNode(QSGNode* node, UpdatePaintNodeData*) override;

private:
    QSize m_size;
    QPixmap* m_pixmap;
};
