#pragma once
#include "core/CommonTypes.h"
#include "ui/InputDevice.h"
#include <QWidget>
#include <QScopedPointer>

class QUndoStack;
class BrushEngine;
class EventFilter;

class Canvas : public QWidget {
    Q_OBJECT
public:
    explicit Canvas(const QSize& size, BrushEngine* brushEngine, EventFilter* eventFilter);

    void setName(const QString& name);
    const QString& name() const;

    void setFilePath(const QString& filePath);
    const QString& filePath() const;

    const QPixmap& buffer() const;

    QUndoStack* undoStack() const;

    void save();
    void open(const QString& filePath);
    void exportPng(const QString& filePath);

    void addLayer(const QString& name = QString());
    void addLayer(const QSharedPointer<Layer>& layer);

    void select();
    void unselect();

    void clear();

    void setCurrentLayerIndex(int index);
    int currentLayerIndex() const;

    Layer* currentLayer() const;

    QString nextName();

signals:
    void colorPicked(const QColor& color);
    void inputDeviceDataChanged(const InputDevice::Data& data);

protected:
    void mouseMoveEvent(QMouseEvent* event) override;
    void mousePressEvent(QMouseEvent* event) override;
    void mouseReleaseEvent(QMouseEvent*) override;

    void paintEvent(QPaintEvent* event) override;

private slots:
    void drawCursor(int size);

    void onKeyPressed(QKeyEvent* event);
    void onKeyReleased(QKeyEvent* event);

private:
    void paintAction(const QPointF& pos);
    QString filePathToName(const QString& filePath) const;

    bool pickPressed() const;
    void pickColor(const QPointF& pos);

    QRect clipBound(const QRect& bound);

    BrushEngine* m_brushEngine = nullptr;
    Layers m_layers;
    int m_currentLayerIndex = -1;
    int m_maxTabCount = 1;
    QString m_name;
    QString m_filePath;
    QUndoStack* m_undoStack = nullptr;
    QPixmap m_buffer;
    QRect m_paintArea;
};
