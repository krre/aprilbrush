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
    QSize size() const { return m_size; }

public slots:
    void setSize(QSize size);

signals:
    void sizeChanged(QSize size);

protected:
    QSGNode* updatePaintNode(QSGNode* node, UpdatePaintNodeData*) override;
    void mouseMoveEvent(QMouseEvent* event) override;
    void mousePressEvent(QMouseEvent* event) override;
    void mouseReleaseEvent(QMouseEvent* event) override;

private:
    QSize m_size;
    QImage* image;
};
