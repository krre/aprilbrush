#pragma once
#include "core/CommonTypes.h"
#include "ui/InputDevice.h"
#include <QWidget>
#include <QScopedPointer>

class QUndoStack;
class BrushEngine;

class Canvas : public QWidget {
    Q_OBJECT
public:
    Canvas(const QSize& size, BrushEngine* brushEngine);
    ~Canvas();

    void setName(const QString& name);
    const QString& name() const;

    void setFilePath(const QString& filePath);
    const QString& filePath() const;

    const QPixmap& buffer() const;

    QUndoStack* undoStack() const;

    void save() const;
    void open(const QString& filePath);
    void exportPng(const QString& filePath) const;

    void addLayer(const QString& name = QString());

    void select();
    void unselect();

    void clear();

    void setCurrentLayerIndex(int index);
    int currentLayerIndex() const;

    Layer* currentLayer();

    QString nextName();

    static QSize defaultSize();

signals:
    void colorPicked(const QColor& color);
    void inputDeviceDataChanged(const InputDevice::Data& data);

protected:
    void mouseMoveEvent(QMouseEvent* event) override;
    void mousePressEvent(QMouseEvent* event) override;
    void mouseReleaseEvent(QMouseEvent*) override;

    void keyPressEvent(QKeyEvent* event) override;
    void keyReleaseEvent(QKeyEvent* event) override;

    void paintEvent(QPaintEvent* event) override;

private slots:
    void drawCursor(int size);

private:
    void paintAction(const QPointF& pos);
    QString filePathToName(const QString& filePath) const;

    bool isAltPressed() const;
    void pickColor(const QPointF& pos);

    QRect clipBound(const QRect& bound) const;

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
