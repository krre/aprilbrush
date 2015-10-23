#pragma once
#include <QtGui>
#include <QtQuick>
#include <QtQml>

class CanvasItem : public QQuickItem
{
    Q_OBJECT
public:
    CanvasItem();
protected:
    QSGNode* updatePaintNode(QSGNode* node, UpdatePaintNodeData*) override;
    void mouseMoveEvent(QMouseEvent* event) override;
    void mousePressEvent(QMouseEvent* event) override;
    void mouseReleaseEvent(QMouseEvent* event) override;
};
