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
    QImage* image() const { return m_image; }

public slots:
    void setSize(QSize size);

signals:
    void sizeChanged(QSize size);

protected:
    QSGNode* updatePaintNode(QSGNode* node, UpdatePaintNodeData*) override;

private:
    QSize m_size;
    QImage* m_image;
};
